// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2002
#include <cstdio>
#include <queue>
#include <algorithm>
#define MAXN 111
#define MP make_pair
using namespace std;
typedef long long ll;
#define gc getchar_unlocked
void getint(ll &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
typedef pair<ll,ll> ii;
typedef pair<ll,ii> iii;
ll matriz[MAXN][MAXN],processado[MAXN][MAXN],n,m;
inline ll aux_func(ll x){
	if(x % 4LL == 0LL) return x;
	if(x % 4LL == 1LL) return 1LL;
	if(x % 4LL == 2LL) return x + 1LL;
	return 0LL;
}
inline ll func(ll x , ll y){
	if(x > y) swap(x,y);
	return aux_func(y) ^ aux_func(x-1);
}
int main(){
	while(scanf("%lld %lld",&n,&m) != EOF){
		for(ll i=1LL;i<=n;i++){
			for(ll j=1LL;j<=m;j++){
				getint(matriz[i][j]);
				processado[i][j] = 0;
			}
		}
		priority_queue<iii, vector<iii>, greater<iii> > Dijkstra;
		Dijkstra.push(MP(0,MP(1,1)));
		while(!Dijkstra.empty()){
			iii davez = Dijkstra.top();
			Dijkstra.pop();
			ll percorrido = davez.first, x = davez.second.first, y = davez.second.second;
			if(processado[x][y]) continue;
			processado[x][y] = 1; 
			if(x == n && y == m){
				printf("%lld\n",percorrido);
				break;
			}
			if(x - 1 >= 1 && !processado[x-1][y]){
				Dijkstra.push(MP(percorrido + func(matriz[x-1][y],matriz[x][y]), MP(x-1,y)));
			}
			if(x + 1 <= n && !processado[x+1][y]){
				Dijkstra.push(MP(percorrido + func(matriz[x+1][y],matriz[x][y]), MP(x+1,y)));
			}
			if(y - 1 >= 1 && !processado[x][y-1]){
				Dijkstra.push(MP(percorrido + func(matriz[x][y-1],matriz[x][y]), MP(x,y-1)));
			}
			if(y + 1 <= m && !processado[x][y+1]){
				Dijkstra.push(MP(percorrido + func(matriz[x][y+1],matriz[x][y]), MP(x,y+1)));
			}
		}
	}
	return 0;
}
