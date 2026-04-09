// using topo sort bfs
// https://leetcode.com/problems/course-schedule/description/

class Solution
{
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> adj(numCourses);
        for (auto &e : prerequisites)
        {
            int u = e[0];
            int v = e[1];
            // 1,0 means 0->1 means 0 should be done before 1
            adj[v].push_back(u);
        }

        vector<int> indegree(numCourses, 0);
        for (int i = 0; i < numCourses; i++)
        {
            for (auto it : adj[i])
            {
                indegree[it]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        int count = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            count++;

            for (auto it : adj[node])
            {
                indegree[it]--;
                if (indegree[it] == 0)
                {
                    q.push(it);
                }
            }
        }
        if (count == numCourses)
        {
            return true;
        }
        return false;
    }
};