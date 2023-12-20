#include<iostream>
#include<unordered_map>
#include<set>
#include<queue>
#include<stack>
using namespace std;

template <typename T>
class graph{
  public:
	unordered_map<T,set<T> > adj;

	void addEdge(T u, T v, bool directed) {
		adj[u].insert(v);
		if(directed==0) adj[v].insert(u);
	}

	void printList(){
		for(auto i:adj) {
			cout << i.first << " --> ";
			for(auto j:i.second){
				cout << j << ", ";
			}
			cout << endl;
		}
	}

	void BFS(char src, unordered_map<char,bool> &visited){
	    queue<char> q;
	    q.push(src);
	    visited[src] = 1;
	
	    while(!q.empty()) {
	        char frontNode = q.front();
	        q.pop();
	
	        cout << frontNode << " ";
	
	        for(auto i:adj[frontNode]){
	            if(!visited[i]) {
	                q.push(i);
	                visited[i] = 1;
	            }
	        }
	    }
	}

	void DFS(char src, unordered_map<char,bool> &visited2) {
		visited2[src] = 1;
	    cout << src << " ";
	
	    for(auto i:adj[src]) {
	        if(!visited2[i])
                DFS(i,visited2);
	    }
		
		//OR WE CAN USE STACK AS BELOW (REMEMBER: BFS->QUEUE n DFS->STACK!!!)
		
		/*stack<char> s;
	    s.push(src);
	    visited2[src] = 1;
	
	    while(!s.empty()) {
	        char frontNode = s.top();
	        s.pop();
	
	        cout << frontNode << " ";
	
	        for(auto i:adj[frontNode]){
	            if(!visited2[i]) {
	                s.push(i);
	                visited2[i] = 1;
	            }
	        }
	    }*/
	}
};

int main(){
	int n,e;
	cout << "Enter number of nodes and edges: ";
	cin >> n >> e;
	
	graph<char> g;
	for(int i=0;i<e;i++) {
		char u, v;
		cin >> u >> v;
		g.addEdge(u,v,0);
	}
	g.printList();

	//BFS
	unordered_map<char,bool> visited;
    for(char i='a';i<'a'+n;i++) {
        if(!visited[i])
            g.BFS(i,visited);
    }
	cout << endl;

	//DFS
	unordered_map<char,bool> visited2;
	for(char i='a';i<'a'+n;i++) {
        if(!visited2[i])
            g.DFS(i,visited2);
    }
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//UNIDRECTED GRAPH CYCLE CHECK-
bool cycleCheckBFS(unordered_map<int,set<int>> &adj, int src, unordered_map<int,bool> &visited) {
    visited[src] = 1;

    queue<int> q;
    q.push(src);

    while(!q.empty()) {
        int frontNode = q.front();
        q.pop();

        int visitedCount = 0; //visitedCount : number of neighbours of frontNode that are already visited
        for(auto neighbour:adj[frontNode]){
            if(!visited[neighbour]) {
                q.push(neighbour);
                visited[neighbour] = 1;
            }
            else visitedCount++; //visitedCount=1 normally(only parent is already visited), but >=2 when cycle is present(parent + some other node(s) is already visited)
        }
        if(visitedCount>=2) return true;
    }
    return false;
}

bool cycleCheckDFS(unordered_map<int,set<int>> &adj, int node, int parent, unordered_map<int,bool> &visited) {
    visited[node] = 1;

    for(auto child:adj[node]) {
        if(!visited[child]) {
            bool cycleDetected = cycleCheckDFS(adj,child,node,visited);
            if(cycleDetected) return true;
        }
        else if(visited[child] && child!=parent) return true;
    }
    return false;
}

string cycleDetection (vector<vector<int>>& edges, int n, int m)
{
    unordered_map<int,set<int>> adj;
    for(int i=0;i<m;i++) {
        adj[edges[i][0]].insert(edges[i][1]);
        adj[edges[i][1]].insert(edges[i][0]);
    }

    unordered_map<int,bool> visited;
	//BFS Cycle Check
    for(int i=0;i<n;i++) {
        if(!visited[i]) {
            bool ans = cycleCheckBFS(adj,i,visited);
            if(ans) return ("Yes");
        }
    }
    return ("No");

	//DFS Cycle Check
	for(int i=0;i<n;i++) {
        if(!visited[i]) {
            bool ans = cycleCheckDFS(adj,i,-1,visited);
            if(ans) return ("Yes");
        }
    }
    return ("No");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//DIRECTED GRAPH CYCLE CHECK-

//DFS-
bool DirectedCycleDFS(unordered_map<int,set<int>> &adj, int node, unordered_map<int,bool> &visited, unordered_map<int,bool> &dfsCall) {
  visited[node] = 1;
  dfsCall[node] = 1;

  for(auto child:adj[node]) {
    if(!visited[child]) {
      bool cycleDetected = DirectedCycleDFS(adj,child,visited,dfsCall);
      if(cycleDetected) return true;
    }
    else if(dfsCall[child]) return true;
  }
  dfsCall[node] = 0;
  return false;
}
int detectCycleInDirectedGraph(int n, vector<pair<int,int>> &edges) {
  unordered_map<int,set<int>> adj;
  for(int i=0;i<edges.size();i++)
    adj[edges[i].first].insert(edges[i].second);

  unordered_map<int,bool> visited;
  unordered_map<int,bool> dfsCall;

  for(int i=1;i<=n;i++) {
    if(!visited[i]) {
        bool ans = DirectedCycleDFS(adj,i,visited,dfsCall);
        if(ans) return 1;
    }
  }
  return 0;
}

//Kahn's Algo/BFS- (Node count in topo sort == total nodes, then ACYCLIC otherwise CYCLIC)
int detectCycleInDirectedGraph(int n, vector<pair<int,int>> &edges) {
  vector<vector<int>> adj(n);
  for(int i=0;i<edges.size();i++)
    adj[edges[i].first].push_back(edges[i].second);

  vector<int> inDegrees(n);
  for(auto i:edges) inDegrees[i.second]++;

  queue<int> q;
  for(int i=0;i<n;i++) if(inDegrees[i]==0) q.push(i);

  int topoCount = 0;

  while(!q.empty()) {
    int front = q.front();
    q.pop();

    topoCount++;

    for(auto neighbour:adj[front]) {
      inDegrees[neighbour]--;
      if(inDegrees[neighbour]==0) q.push(neighbour);
    }
  }

  if(topoCount==n) return false;
  else return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//TOPOLOGICAL SORT:-

//DFS- (Slightly Faster)
void dfsTopo(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &ans) {
    visited[node] = 1;

    for(auto i:adj[node]) {
        if(!visited[i]) dfsTopo(i,adj,visited,ans);
    }
    ans.push_back(node);
}
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)  {
    vector<int> ans;

    vector<vector<int>> adj(v);
    for(int i=0;i<e;i++)
        adj[edges[i][0]].push_back(edges[i][1]);

    vector<bool> visited(v);
    for(int i=0;i<v;i++)
        if(!visited[i])
            dfsTopo(i,adj,visited,ans);

    for(int i=0;i<ans.size()/2;i++) swap(ans[i],ans[ans.size()-1-i]);
    return ans;
}

//Kahn's algo/BFS- (Slightly Slower)
vector<int> topologicalSort(vector<vector<int>> &edges, int v, int e)  {
    vector<vector<int>> adj(v);
    for(int i=0;i<e;i++)
        adj[edges[i][0]].push_back(edges[i][1]);

    vector<int> inDegrees(v);
    for(auto i:edges) inDegrees[i[1]]++;

    queue<int> q;
    for(int i=0;i<v;i++) if(inDegrees[i]==0) q.push(i);

    vector<int> ans;
    while(!q.empty()) {
        int front = q.front();
        q.pop();

        ans.push_back(front);

        for(auto neighbour:adj[front]) {
            inDegrees[neighbour]--;
            if(inDegrees[neighbour]==0) q.push(neighbour);
        }
    }
    return ans;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//SHORTEST PATH:-

//Undirected Graph- (Find parents and then go backwards from the destination to the source)
vector<int> shortestPath( vector<pair<int,int>> edges , int n , int m, int s , int t){
	vector<vector<int>> adj(n+1);
	for(auto i:edges) {
		adj[i.first].push_back(i.second);
		adj[i.second].push_back(i.first);
	}

	vector<bool> visited(n+1);
	visited[s] = true;
	vector<int> parent(n+1);
	parent[s] = -1;

	queue<int> q;
	q.push(s);
	while(!q.empty()) {
		int front = q.front();
		q.pop();
		for(auto i:adj[front]) {
			if(!visited[i]) {
				visited[i] = true;
				parent[i] = front;
				q.push(i);
			}
		}
	}

	vector<int> ans;
	int temp = t;
	while(temp!=-1) {
		ans.push_back(temp);
		temp = parent[temp];
	}

	for(int i=0;i<ans.size()/2;i++) swap(ans[i],ans[ans.size()-1-i]);
	return ans;
}

//Directed Acyclic Graph- (Bellman)
    //1) Bellman Ford Algo- O(V*E)
int bellmonFord(int n, int m, int src, int dest, vector<vector<int>> &edges) {
    vector<int> dist(n+1,INT_MAX);
    dist[src]=0;
    
    for(int j=1;j<=n-1;j++){ //run n-1 times
        for(auto i:edges){
            int u = i[0];
            int v = i[1];
            int wt = i[2];
            if(dist[u]!=INT_MAX) dist[v]=min(dist[v],dist[u]+wt);
        }
    }

    return dist[dest];

    /*To check NEGATIVE CYCLE, run once more. If some distance is updated, then negative cycle present.
    bool negativeCycle = false;
    for(auto i:edges){
        int u = i[0];
        int v = i[1];
        int wt = i[2];
        if(dist[u]!=INT_MAX && dist[v] < dist[u]+wt) negativeCycle = true;
    }
    if(negativeCycle) cout << "Negative Cycle present. Hence, no shortest path" << endl;
    else cout << "Shortest Path=" << dist[dest] << endl;
    */
}

    //2) Topo+Bellman- O(V+E)
void dfsTopo(int node,vector<vector<pair<int,int>>> &adj, vector<bool> &visited, stack<int> &topo) {
    visited[node] = true;
    for(auto i:adj[node]) {
        if(!visited[i.first]) dfsTopo(i.first,adj,visited,topo);
    }
    topo.push(node);
}
int TopoBellman(int n, int m, int src, int dest, vector<vector<int>> &edges) {
    vector<vector<pair<int,int>>> adj(n+1);
    for(auto i:edges) {
        pair<int,int> p = make_pair(i[1],i[2]);
        adj[i[0]].push_back(p);
    }

    vector<bool> visited(n+1);
    stack<int> topo;
    for(int i=1;i<=n;i++) {
        if(!visited[i]) dfsTopo(i,adj,visited,topo);
    }

    vector<int> dist(n+1,INT_MAX);
    dist[src]=0;

    while(!topo.empty()) {
        int u = topo.top();
        topo.pop();

        if(dist[u]!=INT_MAX) {
            for(auto i:adj[u]) {
                int v = i.first;
                int wt = i.second;
                dist[v] = min(dist[v],dist[u]+wt);
            }
        }
    }
    return dist[dest];
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//DIJKSKTRA (shortest path but only positive weights allowed):-
vector<int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source) {
    vector<vector<pair<int,int>>> adj(vertices);
    for(int i=0;i<edges;i++) {
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];
        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    vector<int> dist(vertices,INT_MAX);
    set<pair<int,int>> s; //Creating a set with (distance,node) from the source node. Distance is first because we want least dist wala node on top of the set.
    dist[source] = 0;
    s.insert(make_pair(dist[source],source));

    while(!s.empty()) {
        auto top = *(s.begin());
        s.erase(s.begin());
        int topNodeDist = top.first;
        int topNode = top.second;

        for(auto neighbour:adj[topNode]) {
            if(topNodeDist+neighbour.second < dist[neighbour.first]) {
                
                auto record = s.find(make_pair(dist[neighbour.first],neighbour.first)); //Deleting the node from set if it is already present
                if(record!=s.end()) s.erase(record);

                dist[neighbour.first] = topNodeDist+neighbour.second;
                s.insert(make_pair(dist[neighbour.first],neighbour.first));
            }
        }
    }
    return dist;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//PRIM'S ALGO (for MST):- (1-indexed)
vector<pair<pair<int, int>, int>> calculatePrimsMST(int n, int m, vector<pair<pair<int, int>, int>> &g)
{
    vector<vector<pair<int,int>>> adj(n+1);
    for(auto i:g) {
      adj[i.first.first].push_back({i.first.second, i.second});
      adj[i.first.second].push_back({i.first.first, i.second});
    }

    vector<int> weights(n+1,INT_MAX);
    vector<bool> visited(n+1,false);
    vector<int> parent(n+1,-1);

    weights[1] = 0;
    parent[1] = -1;
    int countVisited = 0;

    while(countVisited!=n) {
        int mini = INT_MAX;
        int u = -1;
        for(int i=1;i<=n;i++) {
            if(!visited[i] && weights[i]<mini) {
                mini = weights[i];
                u = i;
            }
        }

        visited[u] = true;
        countVisited++;

        for(auto i:adj[u]) {
            int v = i.first;
            int w = i.second;
            if(!visited[v] && w < weights[v]) {
                weights[v] = w;
                parent[v] = u;
            }
        }
    }

    vector<pair<pair<int, int>, int>> result;
    for(int i=2;i<=n;i++) result.push_back({{parent[i],i},weights[i]});

    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//KRUSKAL'S ALGO (for MST):- 
int findParent(int node, vector<int> &parent) {
  if(parent[node]==node) return node;
  return parent[node] = findParent(parent[node],parent);
}

void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
  if(rank[u]<rank[v]) parent[u] = v;
  else if(rank[v]<rank[u]) parent[v] = u;
  else {
    parent[v] = u;
    rank[u]++;
  }
}

static bool compare(vector<int>&a,vector<int>&b){
  return (a[2]<b[2]);
}

int minimumSpanningTree(vector<vector<int>>& edges, int n)
{
  vector<int> rank(n,0);
  vector<int> parent(n);
  for(int i=0;i<n;i++) parent[i] = i;

  sort(edges.begin(),edges.end(),compare); //sort edges array based on ascending order of weights

  int weight=0;
  for(int i=0;i<edges.size();i++) {
    int u = findParent(edges[i][0],parent);
    int v = findParent(edges[i][1],parent);
    int w = edges[i][2];
    if(u!=v) {
      weight+=w;
      unionSet(u,v,parent,rank);
    }
  }
  return weight;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//KOSARAJU'S ALGO- (Find no. of strongly connected components)
void dfsTopo(int node, vector<vector<int>> &adj, vector<bool> &topoVisited, stack<int> &topoSt) {
	topoVisited[node] = true;
	for(auto i:adj[node]) {
		if(!topoVisited[i]) dfsTopo(i,adj,topoVisited,topoSt);
	}
	topoSt.push(node);
}

void revDFS(int node, vector<bool> &visited, vector<vector<int>> &adjTranspose) {
	visited[node] = true;
	for(auto i:adjTranspose[node]) {
		if(!visited[i]) revDFS(i,visited,adjTranspose);
	}
}

int stronglyConnectedComponents(int v, vector<vector<int>> &edges) {
	vector<vector<int>> adj(v);
	vector<vector<int>> adjTranspose(v);
	for(auto i:edges) {
		adj[i[0]].push_back(i[1]);
		adjTranspose[i[1]].push_back(i[0]);
	}

	vector<bool> topoVisited(v);
	stack<int> topoSt;

	for(int i=0;i<v;i++) {
		if(!topoVisited[i]) dfsTopo(i,adj,topoVisited,topoSt);
	}

	vector<bool> visited(v);
	int strongConnectedCnt = 0;
	while(!topoSt.empty()) {
		int front = topoSt.top();
		topoSt.pop();

		if(!visited[front]) {
			strongConnectedCnt++;
			revDFS(front,visited,adjTranspose);
		}
	}
	return strongConnectedCnt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

//Find BRIDGES/ARTICULATION POINTS in Graph:- (Tarjan's Algo)
void DFSBridges(int node, int parent, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &discTime, vector<int> &lowDiscTime, int timer, vector<vector<int>> &bridges) {
    visited[node] = true;
    discTime[node] = lowDiscTime[node] = timer;
    timer++;

    for(auto nbr:adj[node]) {
        if(!visited[nbr]) {
            DFSBridges(nbr,node,adj,visited,discTime,lowDiscTime,timer,bridges);
            lowDiscTime[node] = min(lowDiscTime[node],lowDiscTime[nbr]); //possible Back Edge, hence update

            if (lowDiscTime[nbr] > discTime[node]) { //Check Bridge or not
              vector<int> temp;
              temp.push_back(node);
              temp.push_back(nbr);
              bridges.push_back(temp);
            }
        }
        else if(nbr!=parent) {
            lowDiscTime[node] = min(lowDiscTime[node],discTime[nbr]); //Back Edge present
        }
    }
}

void DFSArtiPoints(int node, int parent, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &discTime, vector<int> &lowDiscTime, int timer, vector<bool> &isAP) {
    visited[node] = true;
    discTime[node] = lowDiscTime[node] = timer;
    timer++;

    int children = 0;
    for(auto nbr:adj[node]) {
        if(!visited[nbr]) {
            children++;
            DFSArtiPoints(nbr,node,adj,visited,discTime,lowDiscTime,timer,isAP);
            lowDiscTime[node] = min(lowDiscTime[node],lowDiscTime[nbr]); //possible Back Edge, hence update

            if (lowDiscTime[nbr]>=discTime[node] && parent!=-1) isAP[node] = true; //Check AP or not
        }
        else if(nbr!=parent) {
            lowDiscTime[node] = min(lowDiscTime[node],discTime[nbr]); //Back Edge present
        }
    }
    if(parent==-1 && children>1) isAP[node] = true; //root node with more than 1 child is AP
}

vector<vector<int>> findBridges(vector<vector<int>> &edges, int v, int e) {
    vector<vector<int>> adj(v);
    for(int i=0;i<e;i++) {
        adj[edges[i][0]].push_back(edges[i][1]);
        adj[edges[i][1]].push_back(edges[i][0]);
    }

    // disc[] --> Stores discovery times of visited vertices
    // low[] -- >> earliest visited vertex (the vertex with minimum discovery time) that can be reached from subtree rooted with current vertex
    // parent --> Stores the parent vertex in DFS tree
    vector<bool> visited(v);
    int parent = -1;
    int timer = 0;
    vector<int> discTime(v,-1);
    vector<int> lowDiscTime(v,-1);

    vector<vector<int>> bridges;
    vector<bool> isAP(v,false);
    for(int i=0;i<v;i++) {
        if(!visited[i]) {
            DFSBridges(i,parent,adj,visited,discTime,lowDiscTime,timer,bridges);
            DFSArtiPoints(i,parent,adj,visited,discTime,lowDiscTime,timer,isAP);
        }
    }
    
    vector<int> artiPoints;
    for(int i=0;i<v;i++) if(isAP[i]) artiPoints.push_back(i);
    
    return bridges; //also return artiPoints;
}
////////////////////////////////////////////////////////////////////////////////////////////////////