    bool solvemem(int index, int N , vector<int>& arr, int target, vector<vector<int>> &dp){
        //3 base cases
        if(index >= N) return 0;
        if(target < 0) return 0;
        if(target == 0) return 1;
        
        if(dp[index][target] != -1){
            return dp[index][target];
        }
        int incl = solvemem(index+1, N, arr, target - arr[index],dp);
        int excl = solvemem(index+1, N , arr, target-0,dp);
        
        return dp[index][target] = incl or excl;
    }
    
    bool equalPartition(vector<int>& arr) {
        // code here
        int total = 0;
        int N = arr.size();
        for(int i = 0; i <= N-1; i++){
            total += arr[i];
        }
        
        if(total &1){
            return 0;
        }
        int target = total/2;
        // return solverec(0, N, arr ,target);
        
        vector<vector<int>>dp(N, vector<int>(target+1, -1));
        return solvemem(0, N, arr, target , dp);
    }