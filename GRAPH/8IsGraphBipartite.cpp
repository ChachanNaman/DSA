class Solution
{
private:
    bool bfs(int start, int n, vector<vector<int>> &graph, int color[])
    {
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (auto it : graph[node])
            {
                // if adj node is not colored , give it opposite color
                if (color[it] == -1)
                {
                    color[it] = !color[node];
                    q.push(it);
                }
                // if there is adj already colored and is of same color ,
                // make bipartite false
                else if (color[it] == color[node])
                {
                    return false;
                }
            }
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();
        int color[n];

        for (int i = 0; i < n; i++)
        {
            color[i] = -1;
        }

        for (int i = 0; i < n; i++)
        {
            if (color[i] == -1)
            {
                if (bfs(i, n, graph, color) == false)
                {
                    return false;
                }
            }
        }
        return true;
    }
};