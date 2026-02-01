//https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1?page=1&category=Graph&sortBy=submissions
// SC -> all nodes + dfs list + reccursion -> O(N)+O(N)+O(N) -> O(N)
// TC -> dfs loop for all nodes once + summation of degree of each node -> O(N) + O(2E)


class Solution {
    private:
    void dfs(int node , vector<vector<int>>& adj, int vis[], vector<int>&ls){
        vis[node] = 1;
        ls.push_back(node);
        for(auto it : adj[node]){
            if(!vis[it]){
                dfs(it, adj, vis, ls);
            }
        }
    }
  public:
    vector<int> dfs(vector<vector<int>>& adj) {
        // Code here
        int n = adj.size();
        int vis[n] = {0};
        vector<int>ls; //list that i have to return in end 
        int start = 0;
        dfs(start, adj, vis, ls);
        return ls;
        
    }
};
