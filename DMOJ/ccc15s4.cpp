// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc15s4
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
const int MAXN = 2001;
const int MAXK = 201;
vector<iii> grafo[MAXN];
int processado[MAXN][MAXK],K,N,M,A,B;
int main(){
	scanf("%d %d %d",&K,&N,&M);
	for(int i=1;i<=M;i++){
		int u,v,t,h;
		scanf("%d %d %d %d",&u,&v,&t,&h);
		grafo[u].push_back(MP(v,MP(t,h)));
		grafo[v].push_back(MP(u,MP(t,h)));
	}
	scanf("%d %d",&A,&B);
	priority_queue<iii, vector<iii> ,greater<iii>  > Dijkstra;
	Dijkstra.push(MP(0,MP(-K,A)));
	while(!Dijkstra.empty()){
		iii davez = Dijkstra.top();
		Dijkstra.pop();
		int tempo = davez.first, hull = -davez.second.first, v = davez.second.second;
		if(processado[v][hull]) continue;
		processado[v][hull] = 1;
		if(v == B){
			printf("%d\n",tempo);
			return 0;
		}
		hull *= -1;
		for(int i=0;i<grafo[v].size();i++){
			int u = grafo[v][i].first;
			int t = grafo[v][i].second.first;
			int h = grafo[v][i].second.second;
			if(-hull > h) Dijkstra.push(MP(tempo + t,MP(hull + h,u)));
		}
	}
	printf("-1\n");
	return 0;
}