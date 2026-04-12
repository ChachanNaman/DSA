//Dijkstra Algorithm using sets (better)
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
        
         
        set<pair<int,int>>st;//to store dist and node
        vector<int>dist(V,INT_MAX);
        
        st.insert({0,src});
        dist[src] = 0;
        
        while(!st.empty()){
            auto it = *(st.begin());//Gives iterator to smallest element in the set
            int dis = it.first;
            int node = it.second;
            st.erase(it);//remove the smallest one from set 
            
            for(auto it : adj[node]){
                int adjnode = it.first;
                int edgewt = it.second;
                
                if(dis + edgewt < dist[adjnode]){
                    
                    if(dist[adjnode] != INT_MAX){
                        st.erase({dist[adjnode] , adjnode});
                    }
                    dist[adjnode] = dis + edgewt;
                    st.insert({dist[adjnode], adjnode});
                }
            }
            
            
            
        }
        return dist;
    }
};