class Solution {
public:
    int solve(int index , int diff , vector<int>& nums){
        if(index < 0){//if goes outside when doing --
            return 0;
        }
        int ans = 0;
        for(int j = index-1; j>=0; j--){ //j starting from one step behind of index
            if(nums[index] - nums[j] == diff){
                ans = max(ans , 1 + solve(j, diff, nums));
                //one case solved , now go piche 
            }
        }
        return ans;
    }
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();
        if(n <= 2){ //base case
            //if 1 element then return len 1 and if 2 element return len=2
            //coz no d then
            return n;
        }

        int ans = 0;
        //using 2 for loops -> i for 1st number and j to travel all 2nd numbers forward to it 
        for(int i = 0 ; i < n; i++){
            for(int j = i+1 ; j<n; j++){
                ans = max(ans , 2 + solve(i, nums[j]-nums[i], nums));
                //here i will be the index from where i have to travel backwards
            }
        }
        return ans;
    }

    
};  