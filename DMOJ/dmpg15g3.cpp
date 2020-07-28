// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmpg15g3
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii;
typedef tuple<int,int,int,int> quadra;
const int MAXN = 2*1e5 + 10;

int N,LK,RK,LC,RC;
int tam[MAXN],block[MAXN],kinako[MAXN],croissant[MAXN],bit[MAXN],tamanho_componente;
int nivel[MAXN],pai[MAXN],linearizacao[MAXN],ponteiroDfs,lin_c[MAXN],lin_f[MAXN];
char pao[MAXN];
long long total_pares;

vector<int> grafo[MAXN],ctree[MAXN];
vector<int> distc[MAXN],distk[MAXN];

int dfs_calcula_subarvore(int v,int p){
	tam[v] = 1;
	for(int u : grafo[v]){
		if(u == p || block[u]) continue;
		tam[v] += dfs_calcula_subarvore(u,v);
	}
	return tam[v];
}

void dfs_acha_centroide(int v,int p,ii &resp){
	int mx = tamanho_componente - tam[v];
	for(int u : grafo[v]){
		if(u == p || block[u]) continue;
		dfs_acha_centroide(u,v,resp);
		mx = max(mx,tam[u]);
	}
	resp = min(resp,ii(mx,v));
}

void dfs_distancia_centroide(int v,int p,int depthc,int depthk){
	depthc += croissant[v];
	depthk += kinako[v];
	//printf("%d %d V %d Nivel %d %d %d\n",croissant[v],kinako[v],v,(int)distc[v].size(),depthc,depthk);
	distc[v].push_back(depthc);
	distk[v].push_back(depthk);
	for(int u : grafo[v]){
		if(u == p || block[u]) continue;
		dfs_distancia_centroide(u,v,depthc,depthk);
	}
}

int acha_centroide(int v){
	tamanho_componente = dfs_calcula_subarvore(v,-1);
	ii resp = ii(MAXN,MAXN);
	dfs_acha_centroide(v,-1,resp);
	v = resp.second;
	dfs_distancia_centroide(v,-1,0,0);
	return v;
}

int decompoe(int v){
	v = acha_centroide(v);
	block[v] = 1;
	for(int u : grafo[v]){
		if(block[u]) continue;
		u = decompoe(u);
		ctree[v].push_back(u);
		ctree[u].push_back(v);
	}
	return v;
}

void dfs_arvore_centroide(int v,int p){
	linearizacao[++ponteiroDfs] = v;
	lin_c[v] = ponteiroDfs;
	pai[v] = p;
	for(int u : ctree[v]){
		if(u == p) continue;
		nivel[u] = nivel[v] + 1;
		dfs_arvore_centroide(u,v);
	}
	lin_f[v] = ponteiroDfs;
}

void update(int idx,int delta){
	idx++;
	while(idx < MAXN){
		bit[idx] += delta;
		idx += LSOne(idx);
	}
}

int read(int idx){
	int ans = 0;
	while(idx > 0){
		ans += bit[idx];
		idx -= LSOne(idx);
	}
	return ans;
}

int query(int a,int b){
	a++;b++;
	if(a > b) return 0;
	return read(b) - read(a-1);
}

int checa_intervalo(int a,int b,int L1,int R1,int L2,int R2){
	return (L1 <= a && a <= R1) && (L2 <= b && b <= R2);
}

long long sweepline(vector<ii> pares,int fatorc,int fatork){
	long long contou = 0;
	sort(pares.begin(),pares.end());
	vector<quadra> sweep1,sweep2;
	for(int i = 0;i<pares.size();i++){
		ii par1 = pares[i];
		int lo_c = LC - par1.first + fatorc;
		int hi_c = RC - par1.first + fatorc;
		int lo_k = LK - par1.second + fatork;
		int hi_k = RK - par1.second + fatork;
		if(checa_intervalo(par1.first,par1.second,lo_c,hi_c,lo_k,hi_k)) contou--;
		sweep1.push_back(make_tuple(lo_c - 1,lo_k,hi_k,-1));
		sweep2.push_back(make_tuple(hi_c,lo_k,hi_k,1));
	}
	int ponteiro = 0;
	int i = sweep1.size() - 1,j = sweep2.size() - 1;
	while(i >= 0 || j >= 0){
		quadra sweep;
		if(i < 0){
			sweep = sweep2[j];
			j--;
		}
		else if(j < 0){
			sweep = sweep1[i];
			i--;
		}
		else{
			if(sweep1[i] < sweep2[j]){
				sweep = sweep1[i];
				i--;
			}
			else{
				sweep = sweep2[j];
				j--;
			}
		}
		int x = get<0>(sweep), a = get<1>(sweep),b = get<2>(sweep),c = get<3>(sweep);
		while(ponteiro < pares.size() && x >= pares[ponteiro].first){
			update(pares[ponteiro].second,1);
			ponteiro++;
		}
		if(x > -1) contou += c*query(a,b);
	}
	for(int i = 0;i<ponteiro;i++) update(pares[i].second,-1);
	return contou/2;
}

void dfs_conta_pares(int v,int p){
	//printf("DFS %d\n",v);
	for(int u : ctree[v]){
		if(u == p) continue;
		dfs_conta_pares(u,v);
		vector<ii> temporario;
		for(int i = lin_c[u];i<=lin_f[u];i++){
			int w = linearizacao[i];
			temporario.push_back(ii(distc[w][nivel[v]],distk[w][nivel[v]]));
		}
		total_pares -= sweepline(temporario,croissant[v],kinako[v]);
	}
	vector<ii> temporario;
	for(int i = lin_c[v];i<=lin_f[v];i++){
		int w = linearizacao[i];
		temporario.push_back(ii(distc[w][nivel[v]],distk[w][nivel[v]]));
	}
	total_pares += sweepline(temporario,croissant[v],kinako[v]);
}

int main(){
	scanf("%d %d %d %d %d",&N,&LK,&RK,&LC,&RC);
	scanf("%s",pao);
	for(int i = 1;i<=N;i++){
		croissant[i] = (pao[i-1] == 'C');
		kinako[i] = (pao[i-1] == 'K');
		if(LK <= kinako[i] && kinako[i] <= RK && LC <= croissant[i] && croissant[i] <= RC) total_pares++;
	}
	for(int i = 1;i<N;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	int raiz_centroide = decompoe(1);
	dfs_arvore_centroide(raiz_centroide,-1);
	dfs_conta_pares(raiz_centroide,-1);
	printf("%lld\n",total_pares);
	return 0;
}
