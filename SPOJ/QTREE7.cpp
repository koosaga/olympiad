// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QTREE7/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef tuple<int,int,int> trinca;
const int MAXN = 1e5 + 10;
const int NEG = -1e9 - 10;
const int BUCKET = 320;
vector<int> diferentes;
vector<ii> arestas,especiais;
vector<trinca> perguntas;
int pai[MAXN],lazypai[MAXN],maioral[MAXN],lazymaioral[MAXN],marcado[MAXN],grau[MAXN],aux[MAXN][2],ultima[MAXN],valor[MAXN],cor[MAXN],iteracao,n,q;
int find(int x){return pai[x] = (x == pai[x]) ? x : find(pai[x]);}
void join(int x,int y){
	x = find(x);y = find(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	pai[y] = x;
	maioral[x] = max(maioral[x],maioral[y]);
}
int lazyfind(int x){
	if(ultima[x] != iteracao){
		lazypai[x] = pai[x];
		lazymaioral[x] = maioral[x];
		ultima[x] = iteracao;
	}
	return lazypai[x] = (x == lazypai[x]) ? x : lazyfind(lazypai[x]);
}
void lazyjoin(int x,int y){
	x = lazyfind(x);y = lazyfind(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	lazypai[y] = x;
	lazymaioral[x] = max(lazymaioral[x],lazymaioral[y]);
}
void zerar(){
	for(int i = 1;i<=n;i++){
		pai[i] = i;
		maioral[i] = valor[i];
		marcado[i] = grau[i] = 0;
		aux[i][0] = aux[i][1] = NEG;
	}
}
int main(){
	scanf("%d",&n);
	for(int i = 1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		arestas.push_back(ii(u,v));
	}
	for(int i = 1;i<=n;i++) scanf("%d",&cor[i]);
	for(int i = 1;i<=n;i++) scanf("%d",&valor[i]);
	scanf("%d",&q);
	for(int i = 0;i<q;i++){
		int op = 0,x = 0,y = 0;
		scanf("%d",&op);
		if(op == 2) scanf("%d %d",&x,&y);
		else scanf("%d",&x);
		perguntas.push_back(make_tuple(op,x,y));
	}
	int tot_baldez = (q-1)/BUCKET;
	for(int balde_davez = 0;balde_davez<=tot_baldez;balde_davez++){
		zerar();
		especiais.clear();
		diferentes.clear();
		int lo = balde_davez*BUCKET;
		int hi = min(lo + BUCKET - 1,q-1);
		for(int tempo = lo;tempo<=hi;tempo++){
			int x = get<1>(perguntas[tempo]);
			marcado[x] = 1;
		}
		for(int i = 1;i<=n;i++) if(marcado[i]) diferentes.push_back(i);
		for(int i = 0;i<arestas.size();i++){
			int u = arestas[i].first, v = arestas[i].second;
			u = find(u);
			v = find(v);
			if(!marcado[u] && !marcado[v]){
				if(cor[u] == cor[v]) join(u,v);
			}
		}
		for(int i = 0;i<arestas.size();i++){
			int u = arestas[i].first, v = arestas[i].second;
			u = find(u);
			v = find(v);
			if(!marcado[u] && !marcado[v]) continue;
			grau[u]++;
			grau[v]++;
		}
		for(int i = 0;i<arestas.size();i++){
			int u = arestas[i].first, v = arestas[i].second;
			u = find(u);
			v = find(v);
			if(!marcado[u] && !marcado[v]) continue;
			if(marcado[u] && marcado[v]){
				especiais.push_back(arestas[i]);
				continue;
			}
			if(!marcado[u]) swap(u,v);
			if(grau[v] == 1){
				aux[u][cor[v]] = max(aux[u][cor[v]],maioral[v]);
			}
			else{
				especiais.push_back(arestas[i]);
			}
		}
		for(int tempo = lo;tempo<=hi;tempo++){
			int op = get<0>(perguntas[tempo]), x = get<1>(perguntas[tempo]),y = get<2>(perguntas[tempo]);
			if(op == 1){
				cor[x] ^= 1;
				continue;
			}
			if(op == 2){
				valor[x] = y;
				continue;
			}
			++iteracao;
			for(int i : diferentes){
				ultima[i] = iteracao;
				lazypai[i] = i;
				lazymaioral[i] = max(valor[i],aux[i][cor[i]]);
			}
			for(int i = 0;i<especiais.size();i++){
				int u = especiais[i].first, v = especiais[i].second;
				u = lazyfind(u);
				v = lazyfind(v);
				if(cor[u] == cor[v]) lazyjoin(u,v);
			}
			printf("%d\n",lazymaioral[lazyfind(x)]);
		}
	}
	return 0;
}  
