// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QTREE3/
include <cstdio>
#include <vector>
#define LSOne(S) (S & -(S))
using namespace std;
const int MAXN = 1e5 + 10;
vector<int> grafo[MAXN];
int chainNum,chainPtr,chainHead[MAXN],chainPos[MAXN],chainId[MAXN],reversePos[MAXN],pai[MAXN],tamanho[MAXN],cor[MAXN],bit[MAXN],n,q;
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
int bs_bit(int left,int right){
	int ini = left, fim = right, meio,resp = -1;
	if(query_bit(left,right) == 0) return -1;
	while(ini <= fim){
		meio = (ini+fim)/2;
		//printf("BS %d\n",query_bit(left,meio));
		if(query_bit(left,meio) >= 1){
			resp = meio;
			fim = meio - 1;
		}
		else ini = meio + 1;
	}
	if(resp == -1) return resp;
	return reversePos[resp];
}
void dfs(int x,int p){
	tamanho[x] = 1;
	for(int v : grafo[x]){
		if(v == p) continue;
		pai[v] = x;
		dfs(v,x);
		tamanho[x] += tamanho[v];
	}
}
void HLD(int x,int p){
	if(!chainHead[chainNum]){
		chainHead[chainNum] = x;
	}
	chainId[x] = chainNum;
	chainPos[x] = ++chainPtr;
	reversePos[chainPtr] = x;
	if(tamanho[x] == 1) return;
	int maximo = 0, sc = -1;
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
int query_up(int u){
	int uchain,ultimo = -1;
	while(true){
		//printf("Query Up\n");
		uchain = chainId[u];
		if(uchain == 1){
			int candidato = bs_bit(1,chainPos[u]);
			if(candidato != -1) ultimo = candidato;
			break;
		}
		int candidato = bs_bit(chainPos[chainHead[uchain]],chainPos[u]);
		if(candidato != -1) ultimo = candidato;
		u = chainHead[uchain];
		u = pai[u];
	}
	return ultimo;
}
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	pai[1] = 1;
	dfs(1,-1);
	//printf("DFS\n");
	chainNum = 1;
	HLD(1,-1);
	//printf("HLD\n");
	while(q--){
		int op;
		scanf("%d",&op);
		if(op == 0){
			int u;
			scanf("%d",&u);
			if(cor[u] == 0){
				update_bit(chainPos[u],1);
				cor[u] = 1;
			}
			else{
				update_bit(chainPos[u],-1);
				cor[u] = 0;
			}
		}
		else{
			int u;
			scanf("%d",&u);
			printf("%d\n",query_up(u));
		}
	}
	return 0;
} 
