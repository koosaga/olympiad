// Ivan Carvalho
// Solution to https://dmoj.ca/problem/nccc5s5
#include <bits/stdc++.h>
using namespace std;
  
const int MAXN = 80010;
const int MAXM = 250010;
const int MAXL = 210; 
const int INF = 1e9;
const int dx[8] = {1,1,1,-1,-1,-1,0,0};
const int dy[8] = {0,1,-1,0,1,-1,1,-1};

struct edge{
 
	int to,rev; // node, index in the other adjacency list
	int cap; // residual capacity
 
};
 
vector<edge> adjList[MAXN]; // adjacency list of the edges
int Ev[MAXM],Ei[MAXM]; // BFS edge list
int N,M,bfsPtr; // number of nodes
int dist[MAXN],ok[MAXN];
char entrada[MAXL][MAXL]; 
int conversao[2][MAXL][MAXL];

int h[MAXN]; // heuristic of Tidal Flow
int p[MAXM]; // promised flow of Tidal Flow
int l[MAXN]; // amount of flow in pool of Tidal FLow
 
int TidalFlow(int edgeListSize){
 
	int source = 1, sink = N;
 
	for(int i = 1;i<=N;i++) h[i] = 0; // initializing h[v], for aint 
v
	h[source] = INF; // there is no bound in the flow that can reach 
the source
	
	for(int i = 0;i<edgeListSize;i++){
		int w = Ev[i]; // where it comes from
		int idx = Ei[i]; // index in the adjList
		int v = adjList[w][idx].to; // where it goes
		p[i] = min(adjList[w][idx].cap,h[w]); // the promised is 
the minimum of the heuristic and the capacity
		h[v] += p[i]; // we add the promised capacity to the 
heuristic
	}
 
	if(h[sink] == 0) return 0; // if the heuristic for the sink is 
0, then we are done
 
	for(int i = 1;i<=N;i++) l[i] = 0; // initializing l[v], for aint 
v
	l[sink] = h[sink]; // the amount of flow is the heuristic in the 
sink, initiainty
 
	for(int i = edgeListSize - 1;i>=0;i--){
		int w = Ev[i]; // where it comes from
		int idx = Ei[i]; // index in the adjList
		int v = adjList[w][idx].to; // where it goes
		// the promised is the minimum of the promised before, 
the diference between heuristic and available of the start or the 
available of the end
		p[i] = min(p[i], min(h[w] - l[w],l[v])); 
		l[v] -= p[i];
		l[w] += p[i];
	}
 
	for(int i =1;i<=N;i++) h[i] = 0; // h[v] = 0, for aint v
	h[source] = l[source]; // the amount of pool is the heuristic
	for(int i = 0;i<edgeListSize;i++){
		int w = Ev[i]; // where it comes from
		int idx = Ei[i]; // index in the adjList
		int v = adjList[w][idx].to; // where it goes
		int rev_idx = adjList[w][idx].rev; // index in the other 
adjList
		p[i] = min(p[i],h[w]);
		h[w] -= p[i];
		h[v] += p[i];
		adjList[w][idx].cap -= p[i]; // we update the residual 
capacity
		adjList[v][rev_idx].cap += p[i]; // update reverse edje 
capacity
	}
 
	return h[sink];
 
}
 
int BFS(){
 
	bfsPtr = 0;
	for(int i = 1;i<=N;i++){
		ok[i] = 0;
	}
 
	int source = 1,sink = N;
 
	queue<int> bfs;
	bfs.push(source);
	ok[source] = 1;
	dist[source] = 0;
 
	while(!bfs.empty()){
 
		int v = bfs.front();
		bfs.pop();
 
		for(int i = 0;i<adjList[v].size();i++){
			if(adjList[v][i].cap == 0) continue;
			int u = adjList[v][i].to;
			if(ok[u]) continue;
			ok[u] = 1;
			dist[u] = dist[v] + 1;
			bfs.push(u);
		}
		for(int i = 0;i<adjList[v].size();i++){
			if(adjList[v][i].cap == 0) continue;
			int u = adjList[v][i].to;
			if(dist[v] + 1 == dist[u]){
				Ev[bfsPtr] = v;
				Ei[bfsPtr] = i;
				bfsPtr++;
			}
		}
 
	}
 
	return bfsPtr;
 
}
 
int FordFulkerson(){
 
	int flow = 0;
 
	while(true){
		int augmenting = TidalFlow(BFS());
		if(augmenting == 0) break;
		else flow += augmenting; 
	}
 
	return flow;
 
}
 
void addEdge(int u,int v,int cap){
 
	edge newedge;
	int uPtr = (int)adjList[u].size();
	int vPtr = (int)adjList[v].size();
	
	newedge.to = v;
	newedge.rev = vPtr;
	newedge.cap = cap;
	adjList[u].push_back(newedge);
 
	newedge.to = u;
	newedge.rev = uPtr;
	newedge.cap = 0;
	adjList[v].push_back(newedge);
 
}

inline int is_valid(int x,int y){
	return min(x,y) >= 0 && max(x,y) < N; 
}

char prox(char c){
	if(c == 'C') return 'A';
	else if(c == 'A') return 'L';
	else if(c == 'L') return 'I';
	else return '*';
} 

void processa(int x,int y){

	int v0 = conversao[0][x][y],v1 = conversao[1][x][y];

	addEdge(v0,v1,1);

	if(entrada[x][y] == 'C') addEdge(1,v0,1); // source to start
	else if(entrada[x][y] == 'I') addEdge(v1,N,1); // end to sink

	char nxt = prox(entrada[x][y]);

	vector<int> rdmz = {0,1,2,3,4,5,6,7};
	random_shuffle(rdmz.begin(),rdmz.end());

	for(int i = 0;i<8;i++){
		int nx = x + dx[rdmz[i]], ny = y + dy[rdmz[i]];
		if(!is_valid(nx,ny)) continue;
		if(entrada[nx][ny] == nxt){
			addEdge(v1,conversao[0][nx][ny],1);
		}
	}

}

int main(){
 
 	scanf("%d",&M);
 	N = 1;

 	for(int i = 0;i<M;i++){
 		scanf("%s",entrada[i]);
 		for(int j = 0;j<M;j++){
 			conversao[0][i][j] = ++N;
 			conversao[1][i][j] = ++N;
 		}
 	}
 	N++;

 	for(int i = 0;i<M;i++){
 		for(int j = 0;j<M;j++){
 			processa(i,j);
 		}
 	}

	printf("%d\n",FordFulkerson());
 
	return 0;
 
}
