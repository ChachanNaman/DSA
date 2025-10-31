https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/

class Solution {
public:
    int solveRec(int index , int buy ,vector<int>& prices, int limit ){
        int n = prices.size();
        if(index == n){
            return 0;
        }
        if(limit == 0){
            return 0;
        }

        int profit = 0;

        if(buy){
            int buyKaro = -prices[index] + solveRec(index+1, 0, prices, limit);
            int skipKaro = 0 + solveRec(index+1, 1, prices, limit);
            profit= max(buyKaro , skipKaro);
        }
        else{
            int sellKaro = +prices[index] + solveRec(index+1, 1, prices, limit-1);
            int skipKaro = 0 + solveRec(index+1, 0, prices, limit);
            profit = max(sellKaro , skipKaro);
        }
        return profit;
    }

    int solveMem(int index , int buy ,vector<int>& prices, int limit , vector<vector<vector<int>>> &dp){
        int n = prices.size();

        if(index == n){
            return 0;
        }

        if(limit == 0){
            return 0;
        }

        if(dp[index][buy][limit] != -1){
            return dp[index][buy][limit];
        }
        int profit = 0;

        if(buy){
            int buyKaro = -prices[index] + solveMem(index+1, 0, prices, limit,dp);
            int skipKaro = 0 + solveMem(index+1, 1, prices, limit,dp);
            profit= max(buyKaro , skipKaro);
        }
        else{
            int sellKaro = +prices[index] + solveMem(index+1, 1, prices, limit-1,dp);
            int skipKaro = 0 + solveMem(index+1, 0, prices, limit,dp);
            profit = max(sellKaro , skipKaro);
        }
        return  dp[index][buy][limit] = profit;
    }

int solveTab(vector<int>& prices){
    int n = prices.size();
    vector<vector<vector<int>>>dp(n+1, vector<vector<int>>(2, vector<int>(3,0)));

    for(int index = n-1 ; index>=0 ; index--){
        for(int buy= 0; buy<=1; buy++){
            //limit = 0 already handled in dp -> base case
            for(int limit = 1; limit <= 2; limit ++){
                int profit = 0; 
                if(buy){
                    int buyKaro = -prices[index]+dp[index+1][0][limit];
                    int skipKaro = 0 + dp[index+1][1][limit];
                    profit = max(buyKaro , skipKaro);
                }
                else{
                    int sellKaro = +prices[index]+dp[index+1][1][limit-1];
                    int skipKaro = 0+dp[index+1][0][limit];
                    profit = max(sellKaro , skipKaro);
                }
                dp[index][buy][limit] = profit;
            }  
        }
    }
    return dp[0][1][2];
}   
int solveOpt(vector<int>& prices){
    int n = prices.size();

    vector<vector<int>>curr(2, vector<int>(3,0));
    vector<vector<int>>next(2, vector<int>(3,0));
    
    for(int index = n-1 ; index>=0 ; index--){
        for(int buy= 0; buy<=1; buy++){
            //limit = 0 already handled in dp -> base case
            for(int limit = 1; limit <= 2; limit ++){
                int profit = 0; 
                if(buy){
                    int buyKaro = -prices[index]+next[0][limit];
                    int skipKaro = 0 + next[1][limit];
                    profit = max(buyKaro , skipKaro);
                }
                else{
                    int sellKaro = +prices[index]+next[1][limit-1];
                    int skipKaro = 0+next[0][limit];
                    profit = max(sellKaro , skipKaro);
                }
                curr[buy][limit] = profit;
            }  
        }
        next = curr;
    }
    return next[1][2];
}
    int maxProfit(vector<int>& prices) {
        // return solveRec(0,1,prices, 2); //limit is sent as 2

        int n = prices.size();
        //3d DP -> with limit size set to 3 as -> 0,1,2 an
        // vector<vector<vector<int>>>dp(n, vector<vector<int>>(2, vector<int>(3,-1)));
        // return solveMem(0,1,prices,2, dp);
        // return solveTab(prices);
        return solveOpt(prices);
    }
};