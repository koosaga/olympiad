// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAAPPLE/
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 3*1e5 + 10;
const ii NULO = MP(MAXN,MAXN);
vector<int> grafo[MAXN];
char entrada[MAXN];
int dfsNum,chainNum,chainPtr,vetor[MAXN],nivel[MAXN],chainId[MAXN],chainHead[MAXN],chainPos[MAXN],bit[MAXN],pai[MAXN],tamanho[MAXN],cor[MAXN],n,q;
ii arvore[8*MAXN],vetorzao[2*MAXN];
void update_bit(int pos,int val){
	while(pos < MAXN){
		bit[pos] += val;
		pos += LSOne(pos);
	}
}
int read_bit(int pos){
	int ans = 0;
	while(pos > 0){
		ans += bit[pos];
		pos -= LSOne(pos);
	}
	return ans;
}
int query_bit(int a,int b){
	return read_bit(b) - read_bit(a-1);
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
	update_bit(chainPtr,cor[x]);
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
	int mid = (left + right)/2;
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
	int uchain,vchain;
	vchain = chainId[v];
	int ans = 0;
	while(true){
		uchain = chainId[u];
		if(uchain == vchain){
			ans += query_bit(chainPos[v],chainPos[u]);
			break;
		}
		ans += query_bit(chainPos[chainHead[uchain]],chainPos[u]);
		u = chainHead[uchain];
		u = pai[u];
	}
	return ans;
}
int doQuery(int u,int v){
	int ancestral = LCA(u,v);
	int vertices = nivel[u] + nivel[v] + 1 - 2*nivel[ancestral];
	int qtd = query_up(u,ancestral) + query_up(v,ancestral) - cor[ancestral];
	if(qtd == vertices || qtd == 0) return 1;
	return 0;
}
int main(){
	scanf("%d %d",&n,&q);
	scanf("%s",entrada);
	for(int i=0;i<n;i++){
		cor[i+1] = (entrada[i] == '1');
	}
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		u++;
		v++;
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	pai[1] = 1;
	dfs(1,-1);
	build_seg(1,1,dfsNum);
	HLD(1,-1);
	while(q--){
		int op;
		scanf("%d",&op);
		if(op == 0){
			int i;
			scanf("%d",&i);
			i++;
			if(cor[i] == 0){
				update_bit(chainPos[i],1);
				cor[i] = 1;
			}
			else{
				update_bit(chainPos[i],-1);
				cor[i] = 0;
			}
		}
		else{
			int a,b;
			scanf("%d %d",&a,&b);
			a++;
			b++;
			if(doQuery(a,b)) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}