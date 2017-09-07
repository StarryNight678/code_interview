# java日期类

## Date类

不推荐使用


//生成一个代表当前时间的Date对象.
Date da=new Date();
System.out.println(da.getTime());//1491831962318
//是否在指定日期后
boolean	after(Date when)
Tests if this date is after the specified date.
//是否在指定日期前
boolean	before(Date when)
Tests if this date is before the specified date.

long	getTime()
Returns the number of milliseconds since January 1, 1970, 00:00:00 GMT represented by this Date object.



```java
Date da=new Date();
System.out.println(da.getTime());
//1491831962318

DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
Date dateMy = null;
try {
 dateMy = dateFormat.parse("2016-07-01 11:36:01");
} catch (ParseException e) {
  e.printStackTrace();
}
```

## Class Calendar


 YEAR + MONTH + DAY_OF_MONTH
 YEAR + MONTH + WEEK_OF_MONTH + DAY_OF_WEEK
 YEAR + MONTH + DAY_OF_WEEK_IN_MONTH + DAY_OF_WEEK
 YEAR + DAY_OF_YEAR
 YEAR + DAY_OF_WEEK + WEEK_OF_YEAR


```java
import java.text.SimpleDateFormat;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Date da = new Date();
        System.out.println(da.getTime());
        //1491831962318
        Calendar cal = Calendar.getInstance();
        Date date = cal.getTime();
        System.out.println(date);
        //Mon Apr 10 22:01:21 CST 2017
        System.out.println(cal.get(Calendar.YEAR));
        //2017
        System.out.println(cal.get(Calendar.MONTH));
        //3  从0 开始
        System.out.println(cal.get(Calendar.DATE));
        //10
        System.out.println(cal.get(Calendar.DAY_OF_MONTH));
        //10
        System.out.println(cal.get(Calendar.HOUR_OF_DAY));//24小时制
        //22
        System.out.println(cal.get(Calendar.HOUR));  //12小时制
        //10
        
        //下一天
        //add 自动进位
        cal.set(2017, 4, 1);
        cal.add(Calendar.MONTH, 1);
        cal.add(Calendar.DATE, 1);
        System.out.println(cal.getTime());

        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMdd");
         //格式化当前系统日期
        String dateTime1 = sdf.format(cal.getTime());
        System.out.println(dateTime1);
        //20170602

        SimpleDateFormat dateFm = new SimpleDateFormat("yyyy-MM-dd"); 
        //格式化当前系统日期
        String dateTime2 = dateFm.format(new Date());
        System.out.println(dateTime2);
        //2017-04-10
    }
}


```