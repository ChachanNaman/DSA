//https://leetcode.com/problems/shortest-cycle-in-a-graph/

class Solution {
private:
    int bfs(int src, vector<vector<int>>& adj, int n) {
        vector<int> dist(n, -1);
        vector<int> parent(n, -1);

        queue<int> q;
        q.push(src);
        dist[src] = 0;

        int ans = INT_MAX;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto adjnode : adj[node]) {
                if (dist[adjnode] == -1) {
                    dist[adjnode] = dist[node] + 1;
                    parent[adjnode] = node;
                    q.push(adjnode);
                } else if (parent[node] != adjnode) {
                    ans = min(ans, dist[node] + dist[adjnode] + 1);
                }
            }
        }
        return ans;
    }

public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int res = INT_MAX;
        for (int i = 0; i < n; i++) {
            res = min(res, bfs(i, adj, n));
        }

        return (res == INT_MAX) ? -1 : res;
    }
};

//heh