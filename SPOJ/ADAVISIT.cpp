// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAVISIT/
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 4*1e5 + 10;
const ii NULO = MP(MAXN,MAXN);
int n,dfsNum,chainNum,chainPtr,nivel[MAXN],pai[MAXN],chainPos[MAXN],chainId[MAXN],chainHead[MAXN],bit[MAXN],vetor[MAXN],tamanho[MAXN];
ii arvore[8*MAXN],vetorzao[2*MAXN];
vector<int> grafo[MAXN];
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
		nivel[v] = nivel[x] + 1;
		pai[v] = x;
		dfs(v,x);
		tamanho[x]+=tamanho[v];
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
	int sc = -1,maximo = 0;
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
int query_up(int u,int v){
	int chainv,chainu;
	chainv = chainId[v];
	while(true){
		chainu = chainId[u];
		if(chainv == chainu){
			update_bit(chainPos[v],1);
			update_bit(chainPos[u]+1,-1);
			break;
		}
		update_bit(chainPos[chainHead[chainu]],1);
		update_bit(chainPos[u]+1,-1);
		u = chainHead[chainu];
		u = pai[u];
	}
}
int doQuery(int u,int v){
	int ancestor = LCA(u,v);
	query_up(u,ancestor);
	query_up(v,ancestor);
	update_bit(chainPos[ancestor],-1);
	update_bit(chainPos[ancestor]+1,1);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	pai[1] = -1;
	dfs(1,-1);
	build_seg(1,1,dfsNum);
	chainNum++;
	HLD(1,-1);
	for(int i=1;i<n;i++) doQuery(i,i+1);
	for(int i=1;i<=n;i++) printf("%d\n",query_bit(chainPos[i]));
	return 0;
} 