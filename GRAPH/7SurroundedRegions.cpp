class Solution
{
public:
    void solve(vector<vector<char>> &board)
    {
        int n = board.size();
        int m = board[0].size();

        queue<pair<int, int>> q;
        vector<vector<int>> vis(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
                {
                    if (board[i][j] == 'O')
                    {
                        vis[i][j] = 1;
                        q.push({i, j});
                    }
                }
            }
        }

        while (!q.empty())
        {
            int row = q.front().first;
            int col = q.front().second;

            q.pop();

            int delrow[] = {1, 0, -1, 0};
            int delcol[] = {0, 1, 0, -1};

            for (int i = 0; i < 4; i++)
            {
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];

                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && vis[nrow][ncol] == 0 && board[nrow][ncol] == 'O')
                {
                    vis[nrow][ncol] = 1;
                    q.push({nrow, ncol});
                }
            }
        }

        // mark those Os to X those who are not connected to boundary
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == 'O' && vis[i][j] == 0)
                {
                    board[i][j] = 'X';
                }
            }
        }
    }
};