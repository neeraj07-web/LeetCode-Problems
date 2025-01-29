//Approach-1 - Using DFS
//T.C : O(n^2)
//S.C : O(n)
class Solution {
    // if there is a n edges  and there are n vertices then this is 100 percent sure that there exist a cycle
public:

// bool dfs isliye kyuki humay batana hai hai ki connected hai ya nhi
bool dfs(unordered_map<int, vector<int>>& adj, int u, int v, vector<bool>& visited){
    visited[u]=true;

    if(u== v){ // agar u---->v tak phunch gya tha toh return kardenge true jisse pata chl jayega ki connected hai dono
        return true;
}
for(int &nghr : adj[u]){
    if(visited[nghr]) continue; // agar already visited hai toh hum usse continue kar denge nahi toh

    if(dfs(adj,nghr,v,visited)){
        return true;
    }
}
return false;
}
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
     int n=edges.size();
     // no .of nodes and no. of edges =n

     unordered_map<int, vector<int>> adj;
     for(int i=0; i<n;i++){
        int u=edges[i][0];
        int v= edges[i][1];

        vector<bool>visited(n,false);

        // check kar lunga ki yeh dono nodes present bhi hai ya nahi and yeh dono connect bhi hai ya nahi - dono connected hai ya nahi humay pata chalega using the dfs call threfore hum ismei dfs call kar rhay thay
        if(adj.find(u) != adj.end() && adj.find(v) != adj.end() && dfs(adj,u,v,visited)){
            return edges[i]; // agar already hai toh hum isse return kar denge as edges [i]
        }

        // agar aisa nahi hai (already present nahi hai )toh hum isse push kar denge adj list mei
        adj[u].push_back(v);
        adj[v].push_back(u);
     }   
     return {}; // agar kuch bhi hain toh blank vector bhej dete hai

    }
};


//Approach-2 - Using BFS
//T.C : O(n^2)
//S.C : O(n)
class Solution {
public:
    int n;
    bool bfs(map<int, vector<int>>& mp, int start, int end) {
        vector<bool> visited(n+1, false);
        queue<int> que;
        que.push(start);
        
        while(!que.empty()) {
            int curr = que.front();
            que.pop();
            visited[curr] = true;
            if(curr == end)
                return true;
            
            for(int &x : mp[curr]) {
                if(!visited[x]) {
                    que.push(x);
                }
            }
        }
        return false;
    }
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        map<int, vector<int>> mp;
        n = edges.size();
        
        for(int i = 0; i<n; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            
            //if u and v are already in graph, then we check
            //if this current edge connects them again ?
            //If yes, this edge is unwanted (redundant)
            if(mp.find(u) != mp.end() && mp.find(v) != mp.end() && bfs(mp, u, v))
                return edges[i];
            
            //Else add them to graph
            mp[u].push_back(v);
            mp[v].push_back(u);
        }
        
        return {};
    }
};


//Approach-3 (DSU - Union Find with Path compression)
//T.C : O(n * alpha(n))
//S.C : O(n)
class DSU {
public:
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent.resize(n+1); //1, 2, 3, 4, 5.., n
        rank.resize(n+1);
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if(x == parent[x]) {
            return x;
        }

        return parent[x] = find(parent[x]); //path compression
    }

    void Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        if(x_parent == y_parent) {
            return;
        }

        if(rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } else if(rank[y_parent] > rank[x_parent]) {
            parent[x_parent] = y_parent;
        } else {
            parent[y_parent] = x_parent; //we made x as the parent
            rank[x_parent]++;
        }
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();

        DSU dsu(n);
        //T.C : DSU = alpha(n)

        //T.C : O(n * alpha(n))
        for(auto &edge : edges) { //O(n)
            int u = edge[0];
            int v = edge[1];

            if(dsu.find(u) == dsu.find(v)) {
                return edge;
            }

            dsu.Union(u, v);
        }

        return {};
    }
};

