class Solution {
public:
    // int solveRec(int index, int buy, vector<int>& prices){
    //     if(index == prices.size()){
    //         return 0;
    //     }
    //     int profit = 0;

    //     if(buy){//buy krsakta hu (buy ==1)
    //             //if buy krlia then mark 0 -> to sell first
    //         profit = max( (-prices[index] + solveRec(index+1, 0, prices)) , 
    //                         (0 + solveRec(index+1, 1, prices)) );
    //     }
    //     else{//buy == 0 -> sell the stock 
    //         //if selled that then pass 1 , that you can buy new now
    //         profit = max( (+prices[index] + solveRec(index+1,1, prices)) , ( 0 + solveRec(index+1, 0, prices)) );
    //     }
    //     return profit;
    // }

    // int solveMem(int index, int buy, vector<int>& prices, vector<vector<int>> &dp){
    //     if(index == prices.size()){
    //         return 0;
    //     }

    //     if(dp[index][buy] != -1){
    //         return dp[index][buy];
    //     }
    //     int profit = 0;

    //     if(buy){
    //         int buyKaro = -prices[index] + solveMem(index+1, 0, prices, dp);
    //         int skipKaro = 0 + solveMem(index+1, 1, prices, dp);
    //         profit = max(buyKaro, skipKaro);
    //     }
    //     else{
    //         int sellKaro = +prices[index] + solveMem(index+1,1, prices, dp);
    //         int skipKaro = 0 + solveMem(index+1, 0, prices, dp);
    //         profit = max( sellKaro, skipKaro);
    //     }
    //     return dp[index][buy] = profit;
    // }

    // int solveTab(vector<int>& prices){
    //     int n = prices.size();
    //     vector<vector<int>>dp(n+1 , vector<int>(2,0));
    //     //handled the last index base case in dp 

    //     for(int index = n-1; index>= 0; index--){
    //         for(int buy = 0; buy <= 1; buy++){

    //             int profit = 0;

    //             if(buy){
    //                 int buyKaro = -prices[index] + dp[index+1][0];
    //                 int skipKaro = 0 + dp[index+1][1];
    //                 profit = max(buyKaro, skipKaro);
    //             }
    //             else{
    //                 int sellKaro = +prices[index] +dp[index+1][1];
    //                 int skipKaro = 0 + dp[index+1][0];
    //                 profit = max( sellKaro, skipKaro);
    //             }
    //             dp[index][buy] = profit;
    //         }
    //     }
    //     return dp[0][1];
    // }

    //after seeing problem -> i need only 2 rows to solve like curr and next with 2 cols (1 or 0) for buy 
    int solveOpt(vector<int>& prices){
        int n = prices.size();

        vector<int>curr(2,0);
        vector<int>next(2,0);

        for(int index = n-1; index>= 0; index--){
            for(int buy = 0; buy <= 1; buy++){

                int profit = 0;

                if(buy){
                    int buyKaro = -prices[index] + next[0];
                    int skipKaro = 0 + next[1];
                    profit = max(buyKaro, skipKaro);
                }
                else{
                    int sellKaro = +prices[index] +next[1];
                    int skipKaro = 0 + next[0];
                    profit = max( sellKaro, skipKaro);
                }
                curr[buy] = profit;
            }
            next = curr;
        }
        return next[1];
    } //sc -> o(1) , tc -> o(n)
    int maxProfit(vector<int>& prices) {
        // int n = prices.size();
        // vector<vector<int>>dp(n+1, vector<int>(2, -1));
        // return solveRec(0, 1, prices);
        // return solveMem(0, 1, prices, dp);
        // return solveTab(prices);
        return solveOpt(prices);
    }
};