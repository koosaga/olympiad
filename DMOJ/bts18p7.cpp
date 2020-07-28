// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bts18p7
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
const int MAXL = 18;

vector<int> grafo[MAXN];
int ancestral[MAXN][MAXL],maior[MAXN][MAXL],menor[MAXN][MAXL];
int nivel[MAXN],populacao[MAXN],e1[MAXN],e2[MAXN],e3[MAXN];
int N,Q,R,maxH,LOGH;

void dfs(int v,int p){

	for(int i : grafo[v]){
		int u = (e1[i] != v) ? (e1[i]) : (e2[i]);
		if(u == p) continue;
		ancestral[u][0] = v;
		nivel[u] = nivel[v] + 1;
		maior[u][0] = max(populacao[v],populacao[u]);
		menor[u][0] = e3[i];
		dfs(u,v);   
	}

}

void build(){

	for(int j = 1;j<MAXL;j++){
		for(int i =1;i<=N;i++){
			int z = ancestral[i][j-1];
			if(z == -1) continue;
			ancestral[i][j] = ancestral[z][j-1];
			maior[i][j] = max(maior[i][j-1], maior[z][j-1]);
			menor[i][j] = min(menor[i][j-1], menor[z][j-1]);
		}
	}

}

int LCA(int v,int u){

	if(nivel[v] < nivel[u]) swap(u,v);

	for(int i = LOGH;i>=0;i--){
		int z = ancestral[v][i];
		if(z == -1) continue;
		if(nivel[z] >= nivel[u]) v = z;
	}

	if(u == v) return u;

	for(int i = LOGH;i>=0;i--){
		if(ancestral[v][i] != -1 && ancestral[v][i] != 
ancestral[u][i]){
			v = ancestral[v][i];
			u = ancestral[u][i];
		}
	}

	return ancestral[v][0];

}

int goUp(int v,int h){

	h = nivel[v] - h;

	for(int i = LOGH;i>=0;i--){
		int z = ancestral[v][i];
		if(z == -1) continue;
		if(nivel[z] >= h) v = z;
	}
	return v;

}

int maxPath(int v,int u){
	int ans = populacao[v];
	for(int i = LOGH;i>=0;i--){
		int z = ancestral[v][i];
		if(z == -1) continue;
		if(nivel[z] >= nivel[u]){
			ans = max(ans,maior[v][i]);
			v = z;
		}
	}
	return ans;
}

int minPath(int v,int u){
	int ans = Q+1;
	for(int i = LOGH;i>=0;i--){
		int z = ancestral[v][i];
		if(z == -1) continue;
		if(nivel[z] >= nivel[u]){
			ans = min(ans,menor[v][i]);
			v = z;
		}
	}
	return ans;
}

int buscaSubiu(int v,int u,int k){

	//printf("Busca Subiu\n");

	int ini = 0, fim = nivel[v] - nivel[u],meio,resp = -1;
	while(ini <= fim){
		meio = (ini+fim)/2;
		//printf("I %d M %d F %d\n",ini,meio,fim);
		int w = goUp(v,meio);
		//printf("V %d W %d %d\n",v,w,maxPath(v,w));
		if(maxPath(v,w) >= k){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}

	return goUp(v,resp);

}

int buscaDesceu(int v,int u,int k){

	//printf("Busca Desceu\n");

	int ini = 0, fim = nivel[v] - nivel[u], meio, resp = -1;
	while(ini <= fim){
		meio = (ini+fim)/2;
		int w = goUp(v,meio);
		if(maxPath(w,u) >= k){
			resp = meio;
			ini = meio + 1;
		}
		else{
			fim = meio - 1;
		}
	}

	return goUp(v,resp);

}

int main(){

	scanf("%d %d %d",&N,&Q,&R);
	for(int i = 1;i<=N;i++) scanf("%d",&populacao[i]);
	for(int i = 1;i<N;i++){
		scanf("%d %d",&e1[i],&e2[i]);
		e3[i] = Q+1;
		grafo[e1[i]].push_back(i);
		grafo[e2[i]].push_back(i);
	}

	for(int i = 1;i<=R;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		e3[y] = x;
	}

	for(int j = 0;j<MAXL;j++){
		for(int i = 0;i<=N;i++){
			menor[i][j] = Q+1;
			maior[i][j] = 0;
			ancestral[i][j] = -1;
		}
	}
	dfs(1,-1);
	build();
	for(int i = 1;i<=N;i++) maxH = max(maxH,nivel[i] + 1);
	while((1 << LOGH) <= maxH) LOGH++;

	for(int q = 1;q<=Q;q++){
		int a,b,k;
		scanf("%d %d %d",&a,&b,&k);
		int c = LCA(a,b);
		int meuMin = min(minPath(a,c),minPath(b,c));
		int m1 = maxPath(a,c),m2 = maxPath(b,c);
		int meuMax = max(m1,m2);
		//printf("C %d com D %d e Min %d Max %d (%d,%d)\n",c, 
nivel[a] + nivel[b] - 2*nivel[c], meuMin, meuMax,m1,m2);
		if(q > meuMin || meuMax < k){
			printf("-1\n");
			continue;
		}
		if(m1 >= k) printf("%d\n",buscaSubiu(a,c,k));
		else printf("%d\n",buscaDesceu(b,c,k));
	}

	return 0;

}
