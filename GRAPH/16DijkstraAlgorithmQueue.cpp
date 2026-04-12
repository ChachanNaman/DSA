//Dijkstra Algorithm using priority queue
https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1?page=1&category=Graph&sortBy=submissions
class Solution {
  public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        
        // Step 1: Build adjacency list
        vector<vector<pair<int,int>>> adj(V);
        
        for(auto &e : edges){
            int u = e[0];
            int v = e[1];
            int wt = e[2];
            
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt}); // remove if directed
        }
        
        
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>pq;
        
        vector<int> dist(V, INT_MAX);
        
        dist[src] = 0;
        pq.push({0,src});
        
        while(!pq.empty()){
            int dis = pq.top().first; //get the top element means minimum one 
            int node = pq.top().second;
            pq.pop();
            
            for(auto it : adj[node]){
                int adjnode = it.first;
                int edgewt = it.second;
                
                if(dis + edgewt < dist[adjnode]){ //dis curr + edge weight < distance of adj node 
                    //then update dist of that node 
                    dist[adjnode] = dis + edgewt;
                    pq.push({dist[adjnode], adjnode});
                }
            }
            
        }
        return dist;
        
    }
};