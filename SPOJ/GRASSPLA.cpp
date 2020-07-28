// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GRASSPLA/
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii; 
const int MAXN = 1e5 + 10;
const ii NULO = MP(MAXN,MAXN);
vector<int> grafo[MAXN];
int dfsNum,chainNum,chainPtr,pai[MAXN],nivel[MAXN],vetor[MAXN],chainHead[MAXN],chainId[MAXN],chainPos[MAXN],bit[MAXN],tamanho[MAXN],n,m;
ii arvore[8*MAXN],vetorzao[2*MAXN];
void update_bit(int pos,int val){
	while(pos < MAXN){
		bit[pos] += val;
		pos += LSOne(pos);
	}
}
int query_bit(int pos){
	int ans = 0;
	while(pos > 0){
		ans += bit[pos];
		pos -= LSOne(pos);
	}
	return ans;
}
void dfs(int x,int p){
	vetor[x] = ++dfsNum;
	vetorzao[dfsNum] = MP(nivel[x],x);
	tamanho[x]++;
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
	if(!chainHead[chainNum]){
		chainHead[chainNum] = x;
	}
	chainId[x] = chainNum;
	chainPos[x] = ++chainPtr;
	if(tamanho[x] == 1) return;
	int maximo = 0,sc = -1;
	for(int v : grafo[x]){
		if(v == p) continue;
		if(tamanho[v] > maximo){
			maximo = tamanho[v];
			sc = v;
		}
	}
	HLD(sc,x);
	for(int v : grafo[x]){
		if(v == p || v == sc) continue;
		chainNum++;
		HLD(v,x);
	}
}
void build_seg(int pos,int left,int right){
	if(left == right){
		arvore[pos] = vetorzao[left];
		return;
	}
	int mid = (left+right)/2;
	build_seg(2*pos,left,mid);
	build_seg(2*pos+1,mid+1,right);
	arvore[pos] = min(arvore[2*pos],arvore[2*pos+1]);
}
ii query_seg(int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return NULO;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return min(query_seg(2*pos,left,mid,i,j),query_seg(2*pos+1,mid+1,right,i,j));
}
int LCA(int u,int v){
	return query_seg(1,1,dfsNum,min(vetor[u],vetor[v]),max(vetor[u],vetor[v])).second;
}
void query_up(int u,int v){
	int uchain,vchain;
	vchain = chainId[v];
	while(true){
		uchain = chainId[u];
		if(u == v) break;
		if(uchain == vchain){
			update_bit(chainPos[v]+1,1);
			update_bit(chainPos[u]+1,-1);
			break;
		}
		update_bit(chainPos[chainHead[uchain]],1);
		update_bit(chainPos[u]+1,-1);
		u = chainHead[uchain];
		u = pai[u];
	}
}
void doQuery(int u,int v){
	int ancestral = LCA(u,v);
	query_up(u,ancestral);
	query_up(v,ancestral);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	pai[1] = 1;
	dfs(1,-1);
	//printf("DFS\n");
	build_seg(1,1,dfsNum);
	//printf("SEG\n");
	chainNum++;
	HLD(1,-1);
	//printf("HLD\n");
	while(m--){
		char op;
		scanf(" %c",&op);
		if(op == 'P'){
			int u,v;
			scanf("%d %d",&u,&v);
			doQuery(u,v);
		}
		else{
			int u,v;
			scanf("%d %d",&u,&v);
			if(nivel[u] < nivel[v]) swap(u,v);
			printf("%d\n",query_bit(chainPos[u]));
		}
	}
	return 0;
}