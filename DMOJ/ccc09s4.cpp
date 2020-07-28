// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc09s4
#include <cstdio>
#include <queue>
#include <vector>
#define PB push_back
#define MP make_pair
#define MAXN 5001
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
bool processado[MAXN];
vector<ii> grafo[MAXN];
int main(){
	priority_queue<ii, vector<ii>,greater<ii> > Dijkstra;
	int n,S,k,q;
	getint(n);
	getint(q);
	while(q--){
		int u,v,peso;
		getint(u);
		getint(v);
		getint(peso);
		grafo[u].PB(MP(v,peso));
		grafo[v].PB(MP(u,peso));
	}
	getint(k);
	while(k--){
		int z,pz;
		getint(z);
		getint(pz);
		Dijkstra.push(MP(pz,z));
	}
	getint(S);
	while(!Dijkstra.empty()){
		ii davez = Dijkstra.top();
		Dijkstra.pop();
		int v = davez.second, distancia = davez.first;
		if (v == S){
			printf("%d",distancia);
			return 0;
		}
		if (processado[v]) continue;
		processado[v] = 1;
		for(int i=0;i<grafo[v].size();i++) Dijkstra.push(MP(distancia+grafo[v][i].second,grafo[v][i].first));
	}
	return 0;
}