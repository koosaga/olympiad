// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SALMAN/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
const ll NULO = 1e9;
vector<int> grafo[MAXN];
int ini[MAXN],fim[MAXN],dfsCount,n,q;
ll salario[MAXN],vetor[MAXN],soma[4*MAXN],minimo[4*MAXN],lazy[4*MAXN];
void dfs(int x,int p){
	ini[x] = ++dfsCount;
	vetor[ini[x]] = salario[x];
	for(int v : grafo[x]){
		if(v == p) continue;
		dfs(v,x);
	}
	fim[x] = dfsCount;
}
void propagate(int pos,int left,int right){
	if(lazy[pos] == 0) return;
	soma[pos] += lazy[pos]*1LL*(right - left + 1);
	minimo[pos] += lazy[pos];
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
}
void build(int pos,int left,int right){
	lazy[pos] = 0;
	if(left == right){
		soma[pos] = minimo[pos] = vetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	soma[pos] = soma[2*pos] + soma[2*pos+1];
	minimo[pos] = min(minimo[2*pos],minimo[2*pos+1]);
}
void update(int pos,int left,int right,int i,int j,ll delta){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos] = delta;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,delta);
	update(2*pos+1,mid+1,right,i,j,delta);
	soma[pos] = soma[2*pos] + soma[2*pos+1];
	minimo[pos] = min(minimo[2*pos],minimo[2*pos+1]);
}
ll query_min(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return NULO;
	if(left >= i && right <= j){
		return minimo[pos];
	}
	int mid = (left+right)/2;
	return min(query_min(2*pos,left,mid,i,j),query_min(2*pos+1,mid+1,right,i,j));
}
ll query_sum(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return 0;
	if(left >= i && right <= j){
		return soma[pos];
	}
	int mid = (left+right)/2;
	return query_sum(2*pos,left,mid,i,j) + query_sum(2*pos+1,mid+1,right,i,j);
}
int main(){
	int TC;
	scanf("%d",&TC);
	for(int tc = 1;tc<=TC;tc++){
		scanf("%d %d",&n,&q);
		printf("Case %d:\n",tc);
		for(int i=1;i<=n;i++){
			grafo[i].clear();
		}
		dfsCount = 0;
		for(int i=1;i<=n;i++){
			int p;
			scanf("%d %lld",&p,&salario[i]);
			grafo[p].push_back(i);
		}
		dfs(1,0);
		build(1,1,n);
		while(q--){
			int op,v;
			scanf("%d %d",&op,&v);
			if(op == 1){
				printf("%lld\n",query_sum(1,1,n,ini[v],fim[v]));
			}
			else if(op == 2){
				update(1,1,n, ini[v],fim[v], min(query_min(1,1,n,ini[v],fim[v]), 1000LL)  );
			}
		}
	}
	return 0;
}