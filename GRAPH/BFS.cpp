//https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1?page=1&category=Graph&sortBy=submissions


class Solution
{
public:
    vector<int> bfs(vector<vector<int>> &adj)
    {
        // code here
        int n = adj.size();
        int vis[n] = {0};
        vis[0] = 1;
        queue<int> q;
        q.push(0);
        vector<int> bfs1;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            bfs1.push_back(node);
            for (auto it : adj[node])
            {
                if (!vis[it])
                {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        return bfs1;
    }
};