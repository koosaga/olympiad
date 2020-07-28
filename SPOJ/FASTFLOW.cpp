/*
Tidal Flow Algorithm by M. Fontaine : https://ioinformatics.org/journal/v12_2018_25_41.pdf
Implementation by I. Carvalho
Solution to FASTFLOW : https://www.spoj.com/problems/FASTFLOW/
Note : In this problem, node 1 is the source and node N is the Sink. Also, the edges are bidirectional.
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5010;
const int MAXM = 30010; 
const ll INF = 1e18;

struct edge{

	int to,rev; // node, index in the other adjacency list
	ll cap; // residual capacity

};

vector<edge> adjList[MAXN]; // adjacency list of the edges
int Ev[MAXM],Ei[MAXM]; // BFS edge list
int N,M,bfsPtr; // number of nodes
int dist[MAXN],ok[MAXN];

ll h[MAXN]; // heuristic of Tidal Flow
ll p[MAXM]; // promised flow of Tidal Flow
ll l[MAXN]; // amount of flow in pool of Tidal FLow

ll TidalFlow(int edgeListSize){

	int source = 1, sink = N;

	fill(h,h+N+1,0); // initializing h[v], for all v
	h[source] = INF; // there is no bound in the flow that can reach the source
	
	for(int i = 0;i<edgeListSize;i++){
		int w = Ev[i]; // where it comes from
		int idx = Ei[i]; // index in the adjList
		int v = adjList[w][idx].to; // where it goes
		p[i] = min(adjList[w][idx].cap,h[w]); // the promised is the minimum of the heuristic and the capacity
		h[v] += p[i]; // we add the promised capacity to the heuristic
	}

	if(h[sink] == 0) return 0; // if the heuristic for the sink is 0, then we are done

	fill(l,l+N+1,0); // initializing l[v], for all v
	l[sink] = h[sink]; // the amount of flow is the heuristic in the sink, initially

	for(int i = edgeListSize - 1;i>=0;i--){
		int w = Ev[i]; // where it comes from
		int idx = Ei[i]; // index in the adjList
		int v = adjList[w][idx].to; // where it goes
		// the promised is the minimum of the promised before, the diference between heuristic and available of the start or the available of the end
		p[i] = min(p[i], min(h[w] - l[w],l[v])); 
		l[v] -= p[i];
		l[w] += p[i];
	}

	fill(h,h+N+1,0); // h[v] = 0, for all v
	h[source] = l[source]; // the amount of pool is the heuristic
	for(int i = 0;i<edgeListSize;i++){
		int w = Ev[i]; // where it comes from
		int idx = Ei[i]; // index in the adjList
		int v = adjList[w][idx].to; // where it goes
		int rev_idx = adjList[w][idx].rev; // index in the other adjList
		p[i] = min(p[i],h[w]);
		h[w] -= p[i];
		h[v] += p[i];
		adjList[w][idx].cap -= p[i]; // we update the residual capacity
		adjList[v][rev_idx].cap += p[i]; // update reverse edje capacity
	}

	return h[sink];

}

int BFS(){

	bfsPtr = 0;
	fill(ok,ok+N+1,0);

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
			if(ok[u]){
				if(dist[u] == dist[v] + 1){
					Ev[bfsPtr] = v;
					Ei[bfsPtr] = i;
					bfsPtr++;
				}
				continue;
			}
			ok[u] = 1;
			dist[u] = dist[v] + 1;
			bfs.push(u);
			Ev[bfsPtr] = v;
			Ei[bfsPtr] = i;
			bfsPtr++;
		}

	}

	return bfsPtr;

}

ll FordFulkerson(){

	ll flow = 0;

	while(true){
		ll augmenting = TidalFlow(BFS());
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
	newedge.cap = cap;
	adjList[v].push_back(newedge);

}

int main(){

	scanf("%d %d",&N,&M);

	for(int i = 1;i<=M;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		addEdge(u,v,w);
	}

	printf("%lld\n",FordFulkerson());

	return 0;

}
