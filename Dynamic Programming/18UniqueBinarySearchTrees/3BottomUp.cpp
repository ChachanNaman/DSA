class Solution {
public:
    int solvetab(int n){
        vector<int>dp(n+1, 0);
        dp[0] = dp[1] = 1;

        int ans = 0;

        for(int i = 2; i<=n; i++){//loop for total no. of nodes
            for(int j = 1; j<=i ; j++){//loop for that node -> possible roots
                dp[i] += dp[j-1] * dp[i-j];
            }
        }
        return dp[n];
    }
    int numTrees(int n) {
        return solvetab(n);
    }
};