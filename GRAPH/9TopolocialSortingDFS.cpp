// https://www.geeksforgeeks.org/problems/topological-sort/1?page=1&category=Graph&sortBy=submissions

class Solution
{
public:
    void dfs(int node, vector<vector<int>> &adj, stack<int> &st, int vis[])
    {
        vis[node] = 1;
        for (auto it : adj[node])
        {
            if (!vis[it])
            {
                dfs(it, adj, st, vis);
            }
        }
        st.push(node);
    }
    vector<int> topoSort(int V, vector<vector<int>> &edges)
    {
        // code here
        vector<vector<int>> adj(V);
        for (auto &e : edges)
        {
            int u = e[0];
            int v = e[1];
            adj[u].push_back(v);
        }

        int vis[V] = {0};
        stack<int> st;
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
            {
                dfs(i, adj, st, vis);
            }
        }

        vector<int> ans;
        while (!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};