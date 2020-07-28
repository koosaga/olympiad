// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GSS7/
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
typedef struct node{
	int maximo,maximo_ini,maximo_fim,total;
}no;
no SALVA;
const int MAXN = 1e5 + 10;
const int LIMIT = 10010; 
const ii NULO = MP(MAXN,MAXN);
vector<int> grafo[MAXN];
int dfsNum,chainNum,chainPtr,vetor[MAXN],chainId[MAXN],chainPos[MAXN],chainHead[MAXN],tamanho[MAXN],nivel[MAXN],chainVal[MAXN],pai[MAXN],numero[MAXN],reversePos[MAXN],n,q;
ii arvore[8*MAXN],vetorzao[2*MAXN];
no kadane[4*MAXN];
int lazy[4*MAXN];
no join(no a,no b){
	no resultado;
	resultado.total = a.total + b.total;
	resultado.maximo_ini = max(a.maximo_ini,a.total + b.maximo_ini);
	resultado.maximo_fim = max(a.maximo_fim + b.total,b.maximo_fim);
	resultado.maximo = max(a.maximo,b.maximo);
	resultado.maximo = max(resultado.maximo, a.maximo_fim + b.maximo_ini);
	resultado.maximo = max(resultado.maximo,0);
	return resultado;
}
no troca(no a){
	no temp;
	temp.total = a.total;
	temp.maximo_ini = a.maximo_fim;
	temp.maximo_fim = a.maximo_ini;
	temp.maximo = a.maximo;
	return temp;
}
void build_kadane(int pos,int left,int right){
	//printf("Build Kadane\n");
	lazy[pos] = LIMIT;
	if(left == right){
		kadane[pos].total = chainVal[left];
		kadane[pos].maximo_ini = kadane[pos].maximo_fim = kadane[pos].maximo = max(kadane[pos].total,0);
		return;
	}
	int mid = (left+right)/2;
	build_kadane(2*pos,left,mid);
	build_kadane(2*pos+1,mid+1,right);
	kadane[pos] = join(kadane[2*pos],kadane[2*pos+1]);
}
void update_kadane(int pos,int left,int right,int i,int j,int val){
	//printf("Update Kadane\n");
	if(lazy[pos] != LIMIT){
		kadane[pos].total = (right - left + 1)*lazy[pos];
		kadane[pos].maximo_ini = kadane[pos].maximo_fim = kadane[pos].maximo = max(kadane[pos].total,0);
		if(left != right){
			lazy[2*pos] = lazy[pos];
			lazy[2*pos+1] = lazy[pos];
		}
		lazy[pos] = LIMIT;
	}
	if(left > right || left > j || right < i) return;
	if(left >= i && right <= j){
		kadane[pos].total = (right - left + 1)*val;
		kadane[pos].maximo_ini = kadane[pos].maximo_fim = kadane[pos].maximo = max(kadane[pos].total,0);
		if(left != right){
			lazy[2*pos] = val;
			lazy[2*pos+1] = val;
		}
		return;
	}
	int mid = (left+right)/2;
	update_kadane(2*pos,left,mid,i,j,val);
	update_kadane(2*pos+1,mid+1,right,i,j,val);
	kadane[pos] = join(kadane[2*pos],kadane[2*pos+1]);
}
no query_kadane(int pos,int left,int right,int i,int j){
	//printf("Query Kadane\n");
	if(lazy[pos] != LIMIT){
		kadane[pos].total = (right - left + 1)*lazy[pos];
		kadane[pos].maximo_ini = kadane[pos].maximo_fim = kadane[pos].maximo = max(kadane[pos].total,0);
		if(left != right){
			lazy[2*pos] = lazy[pos];
			lazy[2*pos+1] = lazy[pos];
		}
		lazy[pos] = LIMIT;
	}
	if(left > right || left > j || right < i) return SALVA;
	if(left >= i && right <= j){
		return kadane[pos];
	}
	int mid = (left+right)/2;
	return join(query_kadane(2*pos,left,mid,i,j),query_kadane(2*pos+1,mid+1,right,i,j));
}
void build_lca(int pos,int left,int right){
	//printf("Build LCA\n");
	if(left == right){
		arvore[pos] = vetorzao[left];
		return;
	}
	int mid = (left+right)/2;
	build_lca(2*pos,left,mid);
	build_lca(2*pos+1,mid+1,right);
	arvore[pos] = min(arvore[2*pos],arvore[2*pos+1]);
}
ii query_lca(int pos,int left,int right,int i,int j){
	//printf("Query LCA\n");
	if(left > right || left > j || right < i) return NULO;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return min(query_lca(2*pos,left,mid,i,j),query_lca(2*pos+1,mid+1,right,i,j));
}
int LCA(int u,int v){
	//printf("LCA\n");
	return query_lca(1,1,dfsNum,min(vetor[u],vetor[v]),max(vetor[u],vetor[v])).second;
}
void dfs(int x,int p){
	//printf("DFS\n");
	tamanho[x] = 1;
	vetor[x] = ++dfsNum;
	vetorzao[dfsNum] = MP(nivel[x],x);
	for(int v : grafo[x]){
		if(v == p) continue;
		pai[v] = x;
		nivel[v] = nivel[x] + 1;
		dfs(v,x);
		tamanho[x] += tamanho[v];
		vetorzao[++dfsNum] = MP(nivel[x],x);
	}
}
void HLD(int x,int p){
	//printf("HLD\n");
	if(!chainHead[chainNum]){
		chainHead[chainNum] = x;
	}
	chainPos[x] = ++chainPtr;
	chainId[x] = chainNum;
	chainVal[chainPtr] = numero[x];
	reversePos[chainPtr] = x;
	if(tamanho[x] == 1) return;
	int maximo = 0, sc = -1;
	for(int v : grafo[x]){
		if(v == p) continue;
		if(tamanho[v] > maximo){
			sc = v;
			maximo = tamanho[v];
		}
	}
	HLD(sc,x);
	for(int v : grafo[x]){
		if(v == p || v == sc) continue;
		chainNum++;
		HLD(v,x);
	}
}
vector<ii> query_up(int u,int v){
	int uchain,vchain;
	vchain = chainId[v];
	vector<ii> processo;
	while(true){
		//printf("Query Up\n");
		uchain = chainId[u];
		if(u == v) break;
		if(uchain == vchain){
			//printf("U %d V %d L : %d R : %d\n",u,v,chainPos[v]+1,chainPos[u]);
			processo.push_back(MP(reversePos[chainPos[v]+1],u));
			break;
		}
		//printf("U %d V %d L : %d R : %d\n",u,chainHead[uchain],chainPos[chainHead[uchain]],chainPos[u]);
		processo.push_back(MP(chainHead[uchain],u));
		u = chainHead[uchain];
		u = pai[u];
	}
	return processo;
}
void updateup(int u,int v,int c){
	int uchain,vchain;
	vchain = chainId[v];
	while(true){
		//printf("Update Up\n");
		uchain = chainId[u];
		if(uchain == vchain){
			update_kadane(1,1,chainPtr,chainPos[v],chainPos[u],c);
			break;
		}
		update_kadane(1,1,chainPtr,chainPos[chainHead[uchain]],chainPos[u],c);
		u = chainHead[uchain];
		u = pai[u];
	}
}
int doQuery(int u,int v){
	int ancestral = LCA(u,v);
	//printf("Ancestral %d\n",ancestral);
	vector<ii> resp;
	vector<ii> primeiro = query_up(u,ancestral);
	for(int i=0;i<primeiro.size();i++) resp.push_back(MP(primeiro[i].second,primeiro[i].first));
	resp.push_back(MP(ancestral,ancestral));
	vector<ii> segundo = query_up(v,ancestral);
	reverse(segundo.begin(),segundo.end());
	for(int i=0;i<segundo.size();i++) resp.push_back(segundo[i]);
	no resultado;
	resultado.maximo_fim = resultado.maximo_ini = resultado.maximo = resultado.total = 0;
	for(int i=0;i<resp.size();i++){
		int r = resp[i].second, l = resp[i].first;
		if(chainPos[l] <= chainPos[r]){
			//printf("L %d R %d MAX %d\n",l,r,query_kadane(1,1,chainPtr,chainPos[l],chainPos[r]).maximo);
			resultado = join(resultado,query_kadane(1,1,chainPtr,chainPos[l],chainPos[r]));
		}
		else{
			//printf("L %d R %d MAX %d\n",l,r,troca(query_kadane(1,1,chainPtr,chainPos[r],chainPos[l])).maximo);
			resultado = join(resultado,troca(query_kadane(1,1,chainPtr,chainPos[r],chainPos[l])));
		}
	}
	return resultado.maximo;
}
void doUpdate(int u,int v,int c){
	int ancestral = LCA(u,v);
	updateup(u,ancestral,c);
	updateup(v,ancestral,c);
}
int main(){
	SALVA.maximo = SALVA.maximo_ini = SALVA.maximo_fim = SALVA.total = 0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&numero[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	pai[1] = 1;
	dfs(1,-1);
	build_lca(1,1,dfsNum);
	chainNum++;
	HLD(1,-1);
	build_kadane(1,1,chainPtr);
	//for(int i=1;i<=n;i++){
		//printf("I %d Id %d Head %d Pos %d Pai %d\n",i,chainId[i],chainHead[chainId[i]],chainPos[i],pai[i]);
	//}
	//for(int i=1;i<=n;i++) printf("%d ",chainVal[i]);
	//printf("\n");
	//printf("%d\n",query_kadane(1,1,chainPtr,1,5).maximo);
	scanf("%d",&q);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op == 1){
			int u,v;
			scanf("%d %d",&u,&v);
			printf("%d\n",doQuery(u,v));
		}
		else{
			int u,v,c;
			scanf("%d %d %d",&u,&v,&c);
			doUpdate(u,v,c);
		}
	}
	return 0;
}