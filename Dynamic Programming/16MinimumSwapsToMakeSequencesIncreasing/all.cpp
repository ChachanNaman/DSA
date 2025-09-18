https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/description/
https://www.youtube.com/watch?v=IeT9Qz_vqHo&list=PLDzeHZWIZsTomOPnCiU3J95WufjE36wsb&index=23
//helloo 
//jii
class Solution {
public:
    // int solveRec(vector<int>& nums1, vector<int>& nums2, int index, bool swapped){

    //     if(index == nums1.size()){ //base case -> end of array
    //         return 0;
    //     }

    //     int ans = INT_MAX;
    //     int prev1 = nums1[index-1];
    //     int prev2 = nums2[index-1];
        
    //     //catch part
    //     if(swapped==1){
    //         swap(prev1, prev2);
    //     }

    //     //no swap part
    //     if(nums1[index] > prev1 && nums2[index] > prev2){
    //         ans = solveRec(nums1, nums2, index+1, 0);
    //         //marked swapped==0 and just go forward and solve again
    //     }

    //     //swap needed
    //     if(nums1[index]>prev2 && nums2[index] > prev1){
    //         ans = min(ans, 1 + solveRec(nums1, nums2, index+1, 1));
    //     }
    //     return ans;
    // }   

    // int solveMem(vector<int>& nums1, vector<int>& nums2, int index, bool swapped, vector<vector<int>> &dp){

    //     if(index == nums1.size()){ //base case -> end of array
    //         return 0;
    //     }

    //     if(dp[index][swapped] != -1){
    //         return dp[index][swapped];
    //     }

    //     int ans = INT_MAX;
    //     int prev1 = nums1[index-1];
    //     int prev2 = nums2[index-1];
        
    //     //catch part
    //     if(swapped==1){
    //         swap(prev1, prev2);
    //     }

    //     //no swap part
    //     if(nums1[index] > prev1 && nums2[index] > prev2){
    //         ans = solveMem(nums1, nums2, index+1, 0, dp);
    //         //marked swapped==0 and just go forward and solve again
    //     }

    //     //swap needed
    //     if(nums1[index]>prev2 && nums2[index] > prev1){
    //         ans = min(ans, 1 + solveMem(nums1, nums2, index+1, 1, dp));
    //     }
    //     return dp[index][swapped] = ans;
    // }

//    int solveTab(vector<int>& nums1, vector<int>& nums2){
//         int n = nums1.size();
//         vector<vector<int>>dp(n+1, vector<int>(2,0));

//         for(int index = n-1 ; index >= 1 ; index--){
//             for(int swapped = 1; swapped >= 0 ; swapped--){
//                 int ans = INT_MAX;
//                 int prev1 = nums1[index-1];
//                 int prev2 = nums2[index-1];
                
//                 //catch part
//                 if(swapped==1){
//                     swap(prev1, prev2);
//                 }

//                 //no swap part
//                 if(nums1[index] > prev1 && nums2[index] > prev2){
//                     ans = dp[index+1][0];
//                     //marked swapped==0 and just go forward and solve again
//                 }

//                 //swap needed
//                 if(nums1[index]>prev2 && nums2[index] > prev1){
//                     ans = min(ans, 1 +dp[index+1][1]);
//                 }
//                 dp[index][swapped] = ans;
//                 }
//             }
//         return dp[1][0];
//    }

    The extra row at dp[n][*] is for the base case when recursion would hit index == n:
    we explicitly allocate an extra row dp[n][0] = dp[n][1] = 0 to represent that base case.

   int solveOpt(vector<int>& nums1, vector<int>& nums2){
        int n = nums1.size();
        int swap = 0;
        int noswap = 0;
        int currswap = 0;
        int currnoswap = 0;

        for(int index = n-1 ; index >= 1 ; index--){
            for(int swapped = 1; swapped >= 0 ; swapped--){
                int ans = INT_MAX;
                int prev1 = nums1[index-1];
                int prev2 = nums2[index-1];
                
                //catch part
                if(swapped==1){
                    int temp = prev2;
                    prev2 = prev1;
                    prev1 = temp;
                }

                //no swap part
                if(nums1[index] > prev1 && nums2[index] > prev2){
                    ans = noswap;
                    //marked swapped==0 and just go forward and solve again
                }

                //swap needed
                if(nums1[index]>prev2 && nums2[index] > prev1){
                    ans = min(ans, 1 +swap);
                }
                if(swapped){
                    currswap = ans;
                }
                else{
                    currnoswap = ans;
                }
                }
                swap = currswap;
                noswap = currnoswap;
            }
        return min(swap,noswap);
   }
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        nums1.insert(nums1.begin(), -1);
        nums2.insert(nums2.begin(), -1);

        bool swapped = 0;
        int n = nums1.size();       
        vector<vector<int>>dp(n, vector<int>(2,-1));
        // return solveRec(nums1, nums2, 1, swapped);
        // return solveMem(nums1, nums2, 1, swapped, dp);
        // return solveTab(nums1, nums2);
        return solveOpt(nums1, nums2);
    }
};



//BOTTOM UP -> 
Iteration: index = 4

Prev = nums1[3]=5, nums2[3]=3

Case swapped=0 (previous index NOT swapped)

prev1=5, prev2=3

No swap at 4
Check: nums1[4]=4 > 5 ❌ → invalid
→ do nothing

Swap at 4
Check: nums1[4]=4 > prev2=3 ✅ and nums2[4]=7 > prev1=5 ✅ → valid
Cost = 1 + dp[5][1] = 1 + 0 = 1
ans = 1

So dp[4][0] = 1

Case swapped=1 (previous index WAS swapped)

Now we swap prev values → prev1=3, prev2=5

No swap at 4
Check: 4 > 3 ✅ and 7 > 5 ✅ → valid
Cost = dp[5][0] = 0
ans = 0

Swap at 4
Check: 4 > 5 ❌ → invalid

So dp[4][1] = 0

✅ After index=4:

dp[4][0] = 1
dp[4][1] = 0

Iteration: index = 3

Prev = nums1[2]=3, nums2[2]=2
Case swapped=0
prev1=3, prev2=2
No swap
5 > 3 ✅ and 3 > 2 ✅ → valid
Cost = dp[4][0] = 1
ans = 1

Swap
5 > 2 ✅ and 3 > 3 ❌ → invalid
So dp[3][0] = 1

Case swapped=1
prev1=2, prev2=3
No swap
5 > 2 ✅ and 3 > 3 ❌ → invalid
Swap
5 > 3 ✅ and 3 > 2 ✅ → valid
Cost = 1 + dp[4][1] = 1 + 0 = 1
ans = 1
So dp[3][1] = 1

✅ After index=3:
dp[3][0] = 1
dp[3][1] = 1


Iteration: index = 2

Prev = nums1[1]=1, nums2[1]=1

Case swapped=0

prev1=1, prev2=1

No swap
3 > 1 ✅ and 2 > 1 ✅ → valid
Cost = dp[3][0] = 1

Swap
3 > 1 ✅ and 2 > 1 ✅ → valid
Cost = 1 + dp[3][1] = 1 + 1 = 2
ans = min(1,2) = 1

So dp[2][0] = 1

Case swapped=1

prev1=1, prev2=1 (same here because values are equal)

Same logic → ans = 1

So dp[2][1] = 1

✅ After index=2:

dp[2][0] = 1
dp[2][1] = 1

Iteration: index = 1

Prev = nums1[0]=-1, nums2[0]=-1

Case swapped=0

prev1=-1, prev2=-1

No swap
1 > -1 ✅ and 1 > -1 ✅ → valid
Cost = dp[2][0] = 1

Swap
1 > -1 ✅ and 1 > -1 ✅ → valid
Cost = 1 + dp[2][1] = 1 + 1 = 2
ans = min(1,2) = 1

So dp[1][0] = 1

Case swapped=1

prev1=-1, prev2=-1

Same checks → ans = 1

So dp[1][1] = 1

✅ After index=1:

dp[1][0] = 1
dp[1][1] = 1

Final Answer

We return dp[1][0] = 1

