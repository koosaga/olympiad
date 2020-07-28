// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1447
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#define MAXN 101
#define MP make_pair
using namespace std;
typedef long long ll;
const ll INF  = 1e16;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
vector<ii> grafo[MAXN];
ll cap[MAXN][MAXN],dist[MAXN],n,m,restam,custo,anterior[MAXN],k,instancia;
bool Dijkstra(){
	for(ll i=1;i<=n;i++){
		dist[i] = INF;
		anterior[i] = -1;
	}
	dist[1] = 0;
	priority_queue<ii, vector<ii>, greater<ii> > SSSP;
	SSSP.push(MP(0,1));
	while(!SSSP.empty()){
		ii davez = SSSP.top();
		SSSP.pop();
		ll percorrido = davez.first, v = davez.second;
		if(percorrido > dist[v]) continue;
		if(v == n){
			break;
		}
		for(int i=0;i < grafo[v].size();i++){
			ll u = grafo[v][i].first, peso = grafo[v][i].second;
			if(cap[u][v] < k) peso *= -1;
			if(percorrido + peso < dist[u] && cap[v][u] > 0){
				anterior[u] = v;
				dist[u] =  percorrido + peso;
				SSSP.push(MP(dist[u],u));
			}
		}
	}
	//printf("%lld\n",dist[n]);
	if(dist[n] == INF) return false;
	vi caminho;
	caminho.push_back(n);
	ll atual = n;
	while(atual != 1){
		caminho.push_back(anterior[atual]);
		atual = anterior[atual];
	}
	reverse(caminho.begin(),caminho.end());
	ll temp = restam;
	//printf("%lld",caminho[0]);
	for(ll i=0;i + 1<caminho.size();i++){
		//printf(" %lld",caminho[i+1]);
		temp = min(temp, cap[caminho[i]][caminho[i+1]] );
	}
	//printf("\n");
	restam -= temp;
	for(ll i=0;i + 1<caminho.size();i++){
		cap[caminho[i]][caminho[i+1]] -= temp;
		cap[caminho[i+1]][caminho[i]] += temp;
	}
	return true;
}
void Edmond(){
	while(Dijkstra()){
		if(restam <= 0) break;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<grafo[i].size();j++){
			ll v = grafo[i][j].first;
			if(cap[i][v] < k) custo += (k - cap[i][v])*grafo[i][j].second;
		}
	}
}
int main(){
	while(scanf("%lld %lld",&n,&m) != EOF){
		custo = 0;
		for(int i=1;i<=n;i++){
			grafo[i].clear();
			for(int j=1;j<=n;j++){
				cap[i][j] = 0;
			}
		}
		while(m--){
			ll u,v,peso;
			scanf("%lld %lld %lld",&u,&v,&peso);
			grafo[u].push_back(MP(v,peso));
			grafo[v].push_back(MP(u,peso));
			cap[u][v] = 1;
			cap[v][u] = 1;
		}
		scanf("%lld %lld",&restam,&k);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cap[i][j] *= k;
			}
		}
		Edmond();
		printf("Instancia %lld\n",++instancia);
		if(restam == 0) printf("%lld\n",custo); 
		else printf("impossivel\n");
		printf("\n");
	}
	return 0;
}
