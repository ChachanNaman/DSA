// https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1?page=1&category=Graph&sortBy=submissions

class Solution
{
public:
    vector<int> shortestPath(int V, vector<vector<int>> &edges, int src)
    {

        // first create adj list
        vector<int> adj[V];
        for (auto it : edges)
        {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        int dist[V];
        for (int i = 0; i < V; i++)
        {
            dist[i] = INT_MAX;
        }
        dist[src] = 0;
        queue<int> q;
        q.push(src);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto it : adj[node])
            {
                if (dist[node] + 1 < dist[it])
                { // dist of curr node + 1 < dist of its adj node already
                    dist[it] = dist[node] + 1;
                    q.push(it);
                }
            }
        }

        vector<int> ans(V, -1);
        for (int i = 0; i < V; i++)
        {
            if (dist[i] != INT_MAX)
            {
                ans[i] = dist[i];
            }
        }
        return ans;
    }
};
