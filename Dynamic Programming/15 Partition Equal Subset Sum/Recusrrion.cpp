//https://www.geeksforgeeks.org/problems/subset-sum-problem2014/1 
    
    bool solverec(int index, int N , vector<int>& arr, int target){
        //3 base cases
        if(index >= N) return 0;
        if(target < 0) return 0;
        if(target == 0) return 1;
        
        int incl = solverec(index+1, N, arr, target - arr[index]);
        int excl = solverec(index+1, N , arr, target-0);
        
        return incl or excl;
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
        return solverec(0, N, arr ,target);
    }