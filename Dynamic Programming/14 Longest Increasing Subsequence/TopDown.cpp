class Solution {
  public:

    int solveMem(int n ,vector<int>& arr, int curr , int prev, vector<vector<int>>& dp){
        if(curr == n){//Base Case
            return 0;
        }
        
        if(dp[curr][prev+1] != -1){
            return dp[curr][prev+1];
        }
        //include
        int take =0;
        if(prev == -1 || arr[curr]>arr[prev]){
            take = 1+solveMem(n , arr , curr+1, curr, dp);
        }
        
        //exlude
        int nottake = 0 + solveMem(n , arr, curr+1, prev, dp);
        
        dp[curr][prev+1] = max(take , nottake); //did +1 in prev coz we cant pass -1 in prev 
        //thats why we made -1->n-1 to 0->n
        return dp[curr][prev+1];

    }
    int lis(vector<int>& arr) {
        // code here
        int n = arr.size();
        
        //curr =  0 ->n-1   -> n elements
        //prev = -1 -> n-1  -> n+1 elements
        vector<vector<int>>dp(n , vector<int>(n+1 , -1));
        return solveMem(n , arr , 0, -1, dp);
    }
};

[3, 10, 2, 1, 20]