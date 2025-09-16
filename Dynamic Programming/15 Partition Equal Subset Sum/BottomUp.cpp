bool solvetab(int N, vector<int> &arr, int total)
{
    vector<vector<int>> dp(N + 1, vector<int>((total / 2) + 1, 0));
    // this dp will handle index>=N and target<0 case , as it's initialised with 0

    // to handle target == 0 , have to initialise dp[i][0] with 0 means all rows ka 1st column 0
    for (int i = 0; i <= N; i++)
    {
        dp[i][0] = 1; // making it true
    }

    // index = N handled in dp already
    for (int index = N - 1; index >= 0; index--)
    {
        for (int target = 0; target <= total / 2; target++)
        {
            bool incl = 0;
            if (target - arr[index] >= 0)
            {
                incl = dp[index + 1][target - arr[index]];
            }
            bool excl = dp[index + 1][target - 0];
            dp[index][target] = incl or excl;
        }
    }
    return dp[0][total / 2];
}
bool equalPartition(vector<int> &arr)
{
    // code here
    int total = 0;
    int N = arr.size();
    for (int i = 0; i <= N - 1; i++)
    {
        total += arr[i];
    }

    if (total & 1)
    {
        return 0;
    }
    int target = total / 2;
    // return solverec(0, N, arr ,target);

    // vector<vector<int>>dp(N, vector<int>(target+1, -1));
    // return solvemem(0, N, arr, target , dp);

    return solvetab(N, arr, total);
}
