// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADABERRY/
#include <cstdio>
#include <algorithm>
#include <vector>
#define LSOne(S) (S & (-S))
using namespace std;
const int MAXN = 2*1e5 + 10;
const int MAX2N = 4*1e5 + 20;
const int lo = 0;
const int hi = 1e6;
vector<int> grafo[MAXN],esq[MAX2N],dir[MAX2N],val[MAX2N];
int vetor[MAX2N],numero[MAXN],ini[MAXN],fim[MAXN],dfsNum,segIt[MAX2N],n,m;
void dfs(int x,int p){
	ini[x] = ++dfsNum;
	vetor[dfsNum] = numero[x];
	for(int i = 0;i < grafo[x].size();i++){
		int v = grafo[x][i];
		if(v == p) continue;
		dfs(v,x);
	}
	fim[x] = ++dfsNum;
	vetor[dfsNum] = numero[x];
}
void update_sparse(int id,int pos,int left,int right,int x){
	val[id][pos]++;
	if(left == right) return;
	int mid = (left+right)/2;
	if(x <= mid){
		if(esq[id][pos] == -1){
			segIt[id]++;
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			esq[id][pos] = segIt[id];
		}
		update_sparse(id,esq[id][pos],left,mid,x);
	}
	else{
		if(dir[id][pos] == -1){
			segIt[id]++;
			esq[id].push_back(-1);
			dir[id].push_back(-1);
			val[id].push_back(0);
			dir[id][pos] = segIt[id];
		}
		update_sparse(id,dir[id][pos],mid+1,right,x);
	}
}
int query_sparse(int id,int pos,int left,int right,int i,int j){
	if(left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return val[id][pos];
	} 
	int mid = (left + right)/2;
	int sinistra = (esq[id][pos] == -1) ? 0 : query_sparse(id,esq[id][pos],left,mid,i,j);
	int destra = (dir[id][pos] == -1) ? 0 : query_sparse(id,dir[id][pos],mid+1,right,i,j);
	return sinistra + destra;
}
void update_bit(int posx,int posy){
	while(posx <= dfsNum){
		update_sparse(posx,0,lo,hi,posy);
		posx += LSOne(posx);
	}
}
int read_bit(int posx,int posy){
	int ans = 0;
	while(posx > 0){
		ans += query_sparse(posx,0,lo,hi,lo,posy);
		posx -= LSOne(posx);
	}
	return ans;
}
int query_bit(int a,int b,int c){
	return read_bit(b,c) - read_bit(a-1,c);
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++) scanf("%d",&numero[i]);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%d %d",&u,&v);
		grafo[u].push_back(v);
		grafo[v].push_back(u);
	}
	dfs(0,0);
	//printf("DFS\n");
	for(int i=0;i<=dfsNum+1;i++){
		val[i].push_back(0);
		dir[i].push_back(-1);
		esq[i].push_back(-1);
	}
	//printf("Foi\n");
	for(int i=1;i<=dfsNum;i++){
		update_bit(i,vetor[i]);
	}
	while(m--){
		int a,b;
		scanf("%d %d",&a,&b);
		printf("%d\n",query_bit(ini[a],fim[a],b)/2);
		update_bit(ini[a],b);
		update_bit(fim[a],b);
	}
	return 0;
}