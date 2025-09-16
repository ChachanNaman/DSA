class Solution {
  public:

    int solveTab(int n ,vector<int>& arr){
         vector<vector<int>>dp(n+1 , vector<int>(n+1 , 0));//tp handle curr in include
         
         for(int curr = n-1 ; curr>=0 ; curr--){
             for(int prev = curr-1 ; prev >= -1; prev--){
                 
                 int take = 0;
                 if(prev == -1 || arr[curr]>arr[prev]){
                     take = 1 + dp[curr+1][curr+1];
                 }
                 
                 //exclude
                 int nottake = 0 + dp[curr+1][prev+1];//did +1 here in prev to save from -1
                 dp[curr][prev+1] = max(take , nottake);                 
             }
         }
         return dp[0][0];
    }
    int lis(vector<int>& arr) {
        // code here     
        int n = arr.size();
        //curr =  0 ->n-1   -> n elements
        // //prev = -1 -> n-1  -> n+1 elements
        
        return solveTab(n ,arr);
    }
};

 [5, 8, 3, 7, 9, 1]