// Ivan Carvalho
// Solution to https://www.spoj.com/problems/OTOCI/
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
const int MAXN = 30010;
const ii NULO = MP(MAXN,MAXN);
vector<int> grafo[MAXN];
char entrada[200];
vector<iii> queries;
int dfsNum,chainNum,chainPtr,vetor[MAXN],nivel[MAXN],chainId[MAXN],chainHead[MAXN],chainPos[MAXN],bit[MAXN],pai[MAXN],tamanho[MAXN],cor[MAXN],n,m,dsu[MAXN],peso[MAXN],processado[MAXN];
ii arvore[8*MAXN],vetorzao[2*MAXN];
int find(int x){
	if(x == dsu[x]) return x;
	return dsu[x] = find(dsu[x]);
}
void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(peso[x] < peso[y]){
		dsu[x] = y;
	}
	else if(peso[x] > peso[y]){
		dsu[y] = x;
	}
	else{
		dsu[x] = y;
		peso[y]++;
	}
}
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
	processado[x] = 1;
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
	processado[x] = 1;
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
	int qtd = query_up(u,ancestral) + query_up(v,ancestral) - cor[ancestral];
	return qtd;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&cor[i]);
		dsu[i] = i;
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		scanf("%s",entrada);
		int u,v;
		if(entrada[0] == 'e'){
			scanf("%d %d",&u,&v);
			queries.push_back(MP(0,MP(u,v)));
		}
		else if(entrada[0] == 'p'){
			scanf("%d %d",&u,&v);
			queries.push_back(MP(1,MP(u,v)));
		}
		else if(entrada[0] == 'b'){
			int u,v;
			scanf("%d %d",&u,&v);
			queries.push_back(MP(2,MP(u,v)));
			if(find(u) != find(v)){
				join(u,v);
				grafo[u].push_back(v);
				grafo[v].push_back(u);
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(!processado[i]){
			dfs(i,-1);
		}
	}
	build_seg(1,1,dfsNum);
	for(int i=1;i<=n;i++){
		peso[i] = 0;
		dsu[i] = i;
		processado[i] = 0;
	}
	for(int i=1;i<=n;i++){
		if(!processado[i]){
			HLD(i,-1);
		}
	}
	for(int i=0;i<m;i++){
		int op = queries[i].first, u = queries[i].second.first, v = queries[i].second.second;
		if(op == 0){
			if(find(u) != find(v)){
				printf("impossible\n");
			}
			else{
				printf("%d\n",doQuery(u,v));
			}
		}
		else if(op == 1){
			update_bit(chainPos[u],-cor[u]);
			cor[u] = v;
			update_bit(chainPos[u],cor[u]);
		}
		else if(op == 2){
			if(find(u) != find(v)){
				printf("yes\n");
				join(u,v);
			}
			else{
				printf("no\n");
			}
		}
	}
	return 0;
}