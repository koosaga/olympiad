// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1409
#include <cstdio>
#include <algorithm>
#include <queue>
#define MAXN 1001
#define MP make_pair
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
const int INF = 1e9 + 100;
int life[MAXN],custo[MAXN],processado[MAXN],grafo[MAXN][MAXN],tam[MAXN],m,n,g,k,possivel;
int main(){
	while(true){
		getint(m);
		getint(n);
		getint(g);
		getint(k);
		if(k == 0 && m == 0 && n == 0 && g == 0) break;
		possivel = 0;
		for(int i = 0; i < MAXN;i++){
			tam[i] = custo[i] = processado[i] = 0;
			life[i] = INF;
		}
		life[0] = 0;
		for(int i=1;i<=m;i++){
			int mana,infringe;
			getint(mana);
			getint(infringe);
			for(int j = 1; j < MAXN; j++){
				life[j] = min(life[j], life[max(j - infringe,0)] + mana);
			}
		}
		while(g--){
			int u,v;
			getint(u);
			getint(v);
			grafo[u][tam[u]++] = v;
			grafo[v][tam[v]++] = u;
		}
		while(k--){
			int local,HP;
			getint(local);
			getint(HP);
			custo[local] += life[HP];
		}
		priority_queue<ii, vector<ii>, greater<ii> > Dijkstra;
		Dijkstra.push(MP(custo[1],1));
		while(!Dijkstra.empty()){
			ii davez = Dijkstra.top();
			Dijkstra.pop();
			int v = davez.second, percorrido = davez.first;
			if(v == n){
				printf("%d\n",percorrido);
				possivel = 1;
				break;
			}
			if(processado[v]) continue;
			processado[v] = 1;
			for(int i=0; i < tam[v];i++){
				int u = grafo[v][i];
				Dijkstra.push(MP(percorrido + custo[u],u));
			}
		}
		if(possivel == 0){
			printf("-1\n");
		}
	}
	return 0;
}
