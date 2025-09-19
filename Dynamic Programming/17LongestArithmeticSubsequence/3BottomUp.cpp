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
                //Look back at j < i.
                //If dp[j][diff] exists → extend it:
                //dp[i][diff] = dp[j][diff] + 1

                ans = max(ans, dp[i][diff] );
            }
        }
        return ans;
    }
};

dp[i][diff] = length of arithmetic subsequence ending at index i with difference diff.

i = 1 (nums[1] = 7)
    j = 0 (nums[0] = 1)
    diff = 7 - 1 = 6
    dp[0][6] doesn’t exist → start new subsequence → dp[1][6] = 2
    ans = 2

i = 2 (nums[2] = 10)
    j = 0 → diff = 10 - 1 = 9 → dp[2][9] = 2
    j = 1 → diff = 10 - 7 = 3 → dp[2][3] = 2
    ans = 2

i = 3 (nums[3] = 13)
    j = 0 → diff = 13 - 1 = 12 → dp[3][12] = 2
    j = 1 → diff = 13 - 7 = 6 → dp[1][6] = 2 exists → dp[3][6] = 3
    j = 2 → diff = 13 - 10 = 3 → dp[2][3] = 2 exists → dp[3][3] = 3
    ans = 3

i = 4 (nums[4] = 14)
    j = 0 → diff = 14 - 1 = 13 → dp[4][13] = 2
    j = 1 → diff = 14 - 7 = 7 → dp[4][7] = 2
    j = 2 → diff = 14 - 10 = 4 → dp[4][4] = 2
    j = 3 → diff = 14 - 13 = 1 → dp[4][1] = 2
    ans = 3 (still)

i = 5 (nums[5] = 19)
    j = 0 → diff = 19 - 1 = 18 → dp[5][18] = 2
    j = 1 → diff = 19 - 7 = 12 → dp[5][12] = 2
    j = 2 → diff = 19 - 10 = 9 → dp[5][9] = 2
    j = 3 → diff = 19 - 13 = 6 → dp[3][6] = 3 exists → dp[5][6] = 4 ✅
    j = 4 → diff = 19 - 14 = 5 → dp[5][5] = 2
    ans = 4

Final ans = 4
The sequence is [1, 7, 13, 19] with common difference 6.