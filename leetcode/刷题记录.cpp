

Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].

/*
O(N^2)
time 826 ms
打败 3.94%
*/

```
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector <int> result;
        for(int i=0;i<nums.size();i++)
        for(int j=i+1;j<nums.size();j++)
        {
            if( nums[i]+nums[j] = target)
            {
                result.insert(i);
                result.insert(j);
            }
        }
        return result;
    }
};

```




//Runtime: 13 ms   beats:77.81%


```

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash;
	vector<int> result;
	for (int i = 0; i < nums.size(); i++) {
		int numberToFind = target - nums[i];

		//if numberToFind is found in map, return them
		if (hash.find(numberToFind) != hash.end()) {
			//+1 because indices are NOT zero based
			result.push_back(hash[numberToFind] );
			result.push_back(i );			
			return result;
		}

		//number was not found. Put it in the map.
		hash[nums[i]] = i;
	}
	return result;
      
    }
};
```

