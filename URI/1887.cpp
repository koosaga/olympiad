// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1887
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int,int> quadra;
const int MAXN = 30100;
const int BUCKET = 250;
vector<quadra> arestas,especiais;
vector<int> marca_antes,marca_depois;
int pai[MAXN],peso[MAXN],n,m,q,custo,last[MAXN],interacao,pilha_pai[MAXN],pilha_peso[MAXN];
void zerar(){for(int i = 1;i<=n;i++) pai[i] = i,peso[i] = 1;}
void constroi_pilha(){
	for(int i = 1;i<=n;i++){
		pilha_pai[i] = pai[i];
		pilha_peso[i]= peso[i];
		last[i] = interacao;
	}
}
int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(peso[x] < peso[y]) swap(x,y);
	peso[x] += peso[y];
	pai[y] = x;
}
int find_pilha(int x){
	if(last[x] != interacao){
		last[x] = interacao;
		pilha_pai[x] = pai[x];
		pilha_peso[x] = peso[x];
	}
	if(x == pilha_pai[x]) return x;
	return pilha_pai[x] =  find_pilha(pilha_pai[x]);
}
void join_pilha(int x,int y){
	x = find_pilha(x);
	y = find_pilha(y);
	if(pilha_peso[x] < pilha_peso[y]) swap(x,y);
	pilha_pai[y] = x;
	pilha_peso[x] += pilha_peso[y];
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		arestas.clear();
		marca_depois.clear();
		marca_antes.clear();
		interacao = 0;
		scanf("%d %d %d",&n,&m,&q);
		for(int i = 1;i<=m;i++){
			int u,v,w;
			scanf("%d %d %d",&u,&v,&w);
			arestas.push_back(make_tuple(w,u,v,-1));
			marca_depois.push_back(0);
			marca_antes.push_back(0);
		}
		for(int i = 0;i<q;i++){
			int u,v,w;
			scanf("%d %d %d",&u,&v,&w);
			arestas.push_back(make_tuple(w,u,v,i));
			marca_depois.push_back(0);
			marca_antes.push_back(0);
		}
		int tot_baldes = (q-1)/BUCKET;
		sort(arestas.begin(),arestas.end());
		for(int balde_davez = 0;balde_davez<=tot_baldes;balde_davez++){
			zerar();
			especiais.clear();
			custo = 0;
			int lo = balde_davez*BUCKET;
			int hi = min((balde_davez+1)*BUCKET - 1,q-1);
			for(int i = 0;i<arestas.size();i++) marca_antes[i] = marca_depois[i] = 0;
			for(int i = 0;i<arestas.size();i++){
				int u = get<1>(arestas[i]),v = get<2>(arestas[i]),t = get<3>(arestas[i]),w = get<0>(arestas[i]);
				if(t >= lo) continue;
				if(find(u) != find(v)){
					join(u,v);
					marca_antes[i] = 1;
				}
			}
			zerar();
			for(int i = 0;i<arestas.size();i++){
				int u = get<1>(arestas[i]),v = get<2>(arestas[i]),t = get<3>(arestas[i]),w = get<0>(arestas[i]);
				if(t > hi) continue;
				if(find(u) != find(v)){
					join(u,v);
					marca_depois[i] = 1;
				}
			}
			zerar();
			for(int i = 0;i<arestas.size();i++){
				int u = get<1>(arestas[i]),v = get<2>(arestas[i]),t = get<3>(arestas[i]),w = get<0>(arestas[i]);
				if(t > hi) continue;
				if(lo <= t && t <= hi){
					especiais.push_back(arestas[i]);
				}
				if(marca_antes[i] == 0) continue;
				if(marca_depois[i] == 1){
					//printf("Sempre U %d V %d W %d\n",u,v,w);
					join(u,v);
					custo += w;
				}
				else{
					especiais.push_back(arestas[i]);
				}
			}
			constroi_pilha();
			for(int tempo = lo;tempo<=hi;tempo++){
				int delta = 0;
				interacao++;
				for(int i = 0;i<especiais.size();i++){
					int u = get<1>(especiais[i]),v = get<2>(especiais[i]),t = get<3>(especiais[i]),w = get<0>(especiais[i]);
					if(t > tempo) continue;
					if(find_pilha(u) != find_pilha(v)){
						//printf("U %d V %d W %d\n",u,v,w);
						join_pilha(u,v);
						delta += w;
					}
				}
				printf("%d\n",custo + delta);
			}
		}
	}
	return 0;
}
