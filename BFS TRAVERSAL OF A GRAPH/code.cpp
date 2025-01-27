class Solution {
  public:
  void DFS(unordered_map<int,vector<int>>& adj, int u,vector<bool>& visited ,vector<int>& result ){
      if(visited [u] == true) return;
      
      visited[u]=true;
      result.push_back(u); // jo visit ho gaya hai ussse result mei dalte jayenge
      
      for(int &v : adj[u]){ // ab is vertex u ke liye kon kon se vertex v tak jaa sakte hai
          if(!visited[v]){
              DFS(adj,v,visited,result); 
          }
      }
  }
    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(vector<vector<int>>& mp) {
        int V=mp.size();
       
       // apnakhud ka ek adjacency list bana rhay thay but already unhone de rakha tha adj list as adj but humne usse rename karke mp kar diya
       unordered_map<int,vector<int>>adj;
        for(int u=0;u<V;u++){
            // ab dekhenge is node 0 se kahan kahan jaa sakte hai
            for(auto v = mp[u].begin(); v!= mp[u].end();v++){
                adj[u].push_back(*v);// is particular node u se kon ko se v pe jaa sakte hai
            }
        }
        
        // result k liye
        vector<int> result;
        vector<bool> visited(V, false);// V size ka visited array liya hai to store whether the nodes are visited or not
        
        DFS(adj, 0, visited , result);// initially we will start it from the node 0
        return result;
    }
};
