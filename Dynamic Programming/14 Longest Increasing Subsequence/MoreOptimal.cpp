//TC : O(nlogn)
//SC : O(n)

class Solution {
  public:
    
    int solveOptimal(int n ,vector<int>& arr){
        if(n==0){
            return 0;
        }
        
        vector<int> ans;
        ans.push_back(arr[0]); //push 1st element always
        
        for(int i = 1; i<n ; i++){
            if(arr[i]>ans.back()){//if normal condn curr ele greater than last ele
                ans.push_back(arr[i]);
            }
            else{//if smaller then find the index of just bada element
                int index = lower_bound(ans.begin(), ans.end() , arr[i])-ans.begin();
                ans[index] = arr[i];
            }
        }
        return ans.size();
    }
    
    
    
    int lis(vector<int>& arr) {
        // code here
        int n = arr.size();

        return solveOptimal( n ,arr);
    }
};