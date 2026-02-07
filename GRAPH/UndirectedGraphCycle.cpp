class Solution
{
private:
    bool dfs(int node, int parent, vector<vector<int>> &adj, vector<int> &vis)
    {
        vis[node] = true;
        for (auto adjnode : adj[node])
        {

            if (!vis[adjnode])
            {
                if (dfs(adjnode, node, adj, vis))
                    return true;
            }
            else if (adjnode != parent)
            {
                return true;
            }
        }
        return false;
    }

public:
    bool isCycle(int V, vector<vector<int>> &edges)
    {
        // Code here
        vector<vector<int>> adj(V);
        for (auto &e : edges)
        {

            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> vis(V, 0);

        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                if (dfs(i, -1, adj, vis))
                {
                    return true;
                }
            }
        }
        return false;
    }
};