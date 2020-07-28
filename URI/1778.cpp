// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1778
#include <cstdio>
#define MAXN 1001
typedef long long ll;
const ll INF = 1e15;
ll n,m,f,p,q,TC;
ll monstro[10*MAXN],hpmonstro[10*MAXN];
ll adj[MAXN][MAXN],grau[MAXN];
ll fila1[MAXN*(MAXN+10)],fila2[MAXN*(MAXN+10)],processado[MAXN],ini,fim,origem,capacidade;
ll custo[MAXN],matriz[MAXN][MAXN],distancia[MAXN],dano;
void bfs(){
	ini = fim = 1;
	fila1[ini] = origem;
	fila2[ini] = 0;
	for(ll i=1;i<=n;i++){
		processado[i] = 0;
	}
	processado[f] = 1;
	while(ini <= fim && fila2[ini] <= capacidade){
		//printf("bfs\n");
		ll vertice = fila1[ini];
		ll percorrido = fila2[ini++];
		if(processado[vertice]) continue;
		processado[vertice] = 1;
		custo[vertice] += dano;
		for(ll i=0;i<grau[vertice];i++){
			ll u = adj[vertice][i];
			if(processado[u]) continue;
			fila1[++fim] = u;
			fila2[fim] = percorrido + 1;
		}
	}
}
void Dijkstra(){
	for(ll i=1;i<=n;i++){
		distancia[i] = matriz[origem][i];
		processado[i] = 0;
	}
	processado[origem] = 1;
	distancia[origem] = 0;
	while(true){
		ll davez = -1;
		ll menor = INF;
		for(ll i=1;i<=n;i++){
			if(!processado[i] && distancia[i] < menor){
				davez = i;
				menor = distancia[i];
			}
		}
		if(davez == -1) break;
		processado[davez] = 1;
		for(ll i=1;i<=n;i++){
			if(distancia[davez] + matriz[davez][i] < distancia[i]){
				distancia[i]  = distancia[davez] + matriz[davez][i];
			}
		}
	}
}
int main(){
	scanf("%lld",&TC);
	for(ll tc=1;tc<=TC;tc++){
		scanf("%lld %lld %lld",&n,&m,&f);
		for(ll i=1;i<=n;i++){
			grau[i] = 0;
			custo[i] = 0;
			for(ll j=1;j<=n;j++){
				matriz[i][j] = INF;
			}
		}
		while(m--){
			ll u,v;
			scanf("%lld %lld",&u,&v);
			adj[u][grau[u]++] = v;
			adj[v][grau[v]++] = u;
		}
		scanf("%lld",&p);
		while(p--){
			scanf("%lld %lld %lld",&origem,&dano,&capacidade);
			bfs();
		}
		scanf("%lld",&q);
		for(ll i=1;i<=q;i++){
			scanf("%lld %lld",&monstro[i],&hpmonstro[i]);
		}
		for(ll i=1;i<=n;i++){
			for(ll j=0;j<grau[i];j++){
				matriz[i][adj[i][j]] = custo[adj[i][j]];
			}
			matriz[i][i] = 0;
		}
		origem = f;
		Dijkstra();
		ll resp = 0;
		for(ll i=1;i<=q;i++){
			//printf("%lld %lld\n",(ll)hpmonstro[i],distancia[monstro[i]]);
			if((ll)hpmonstro[i] > distancia[monstro[i]]){
				resp++;
			}
		}
		printf("Caso #%lld: %lld\n",tc,resp);
	}
	return 0;
}
