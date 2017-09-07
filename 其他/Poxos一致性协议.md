# Posox协议 

首先将议员的角色分为proposers，acceptors，和learners（允许身兼数职）。proposers提出提案，提案信息包括提案**编号和提议的value**；acceptor收到提案后可以接受（accept）提案，若提案获得多数acceptors的接受，则称该提案被批准（chosen）；learners只能“学习”被批准的提案。划分角色后，就可以更精确的定义问题：

1. 决议（value）只有在被proposers提出后才能被批准（未经批准的决议称为“提案（proposal）”）；
1. 在一次Paxos算法的执行实例中，只批准（chosen）一个value；
1. learners只能获得被批准（chosen）的value。

约束:

P1：一个acceptor必须接受（accept）第一次收到的提案。


注意P1是不完备的。如果恰好一半acceptor接受的提案具有value A，另一半接受的提案具有value B，那么就无法形成多数派，无法批准任何一个value。
约束2并不要求只批准一个提案，暗示可能存在多个提案。只要提案的value是一样的，批准多个提案不违背约束2。于是可以产生约束P2：

P2：一旦一个具有value v的提案被批准（chosen），那么之后批准（chosen）的提案必须具有value v。

**算法的内容**



通过一个决议分为两个阶段：

1. prepare阶段：

	- proposer选择一个提案编号n并将prepare请求发送给acceptors中的一个多数派；
	- acceptor收到prepare消息后，如果提案的编号大于它已经回复的所有prepare消息，则acceptor将自己上次接-受的提案回复给proposer，并承诺不再回复小于n的提案；

1. 批准阶段:

	- 当一个proposer收到了多数acceptors对prepare的回复后，就进入批准阶段。它要向回复prepare请求的acceptors发送accept请求，包括编号n和根据P2c决定的value（如果根据P2c没有已经接受的value，那么它可以自由决定value）。
	- 在不违背自己向其他proposer的承诺的前提下，acceptor收到accept请求后即接受这个请求。

这个过程在任何时候中断都可以保证正确性。例如如果一个proposer发现已经有其他proposers提出了编号更高的提案，则有必要中断这个过程。因此为了优化，在上述prepare过程中，如果一个acceptor发现存在一个更高编号的提案，则需要通知proposer，提醒其中断这次提案。


例子:

用实际的例子来更清晰地描述上述过程：

有A1, A2, A3, A4, A5 5位议员，就税率问题进行决议。议员A1决定将税率定为10%,因此它向所有人发出一个草案。这个草案的内容是：
现有的税率是什么?如果没有决定，则建议将其定为10%.时间：本届议会第3年3月15日;提案者：A1

在最简单的情况下，没有人与其竞争;信息能及时顺利地传达到其它议员处。

于是, A2-A5回应：
我已收到你的提案，等待最终批准

而A1在收到2份回复后就发布最终决议：
税率已定为10%,新的提案不得再讨论本问题。

**这实际上退化为二阶段提交协议。**

