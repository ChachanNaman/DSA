class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        //bottom up approach
        int n = nums.size();
        if(n<=2){ //base case
            return n;
        }
        int ans = 0;

        unordered_map<int, int>dp[n+1];

        for(int i = 1; i<n; i++){ //start from 1 bcz j is coming toward i , soo that j-i is valid , we cant stand at same point
            for(int j = 0 ; j < i ; j++){//j start from 0 for every i and travel till i
                int diff = nums[i] -nums[j];

                int count = 1; //already 1 bcz count on which i stnding already

                //check if answer already exist at j index or not
                if(dp[j].count(diff)){
                    count = dp[j][diff]; //include that in count if found 
                }

                dp[i][diff] = 1 + count;
                ans = max(ans, dp[i][diff] );
            }
        }
        return ans;
    }
};