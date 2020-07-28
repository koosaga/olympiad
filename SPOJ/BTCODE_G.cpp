// Ivan Carvalho
// Solution to https://www.spoj.com/problems/BTCODE_G/
#include <bits/stdc++.h>
#define gc getchar_unlocked
inline void getint(int &x){
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
const int MAXN = 1e5 + 10;
const int MAXL = 19;
int ancestral[MAXN][MAXL],chainId[MAXN],chainPos[MAXN],chainHead[MAXN],chainPtr,chainNum,nivel[MAXN],seg[4*MAXN],sz[MAXN],n,q;
vector<int> grafo[MAXN];
int dfs(int v,int p){
	sz[v] = 1;
	for(int i = 1;i<MAXL;i++){
		int u = ancestral[v][i-1];
		if(u != -1){
			ancestral[v][i] = ancestral[u][i-1];
		}
	}
	for(int u : grafo[v]){
		if(u == p) continue;
		nivel[u] = nivel[v] + 1;
		ancestral[u][0] = v;
		sz[v] += dfs(u,v);
	}
	return sz[v];
}
void HLD(int v,int p){
	if(chainHead[chainNum] == 0){
		chainHead[chainNum] = v;
	}
	chainId[v] = chainNum;
	chainPos[v] = ++chainPtr;
	int big = -1,mx = -1;
	for(int u : grafo[v]){
		if(u == p) continue;
		if(sz[u] > mx){
			mx = sz[u];
			big = u;
		}
	}
	if(big != -1) HLD(big,v);
	for(int u : grafo[v]){
		if(u == p || u == big) continue;
		chainNum++;
		HLD(u,v);
	}
}
void update(int pos,int left,int right,int x,int val){
	if(left == right){
		seg[pos] = val;
		return;
	}
	int mid = (left+right)/2;
	if(x<=mid){
		update(2*pos,left,mid,x,val);
	}
	else{
		update(2*pos+1,mid+1,right,x,val);
	}
	seg[pos] = (seg[2*pos] | seg[2*pos+1]);
}
int segquery(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j) return seg[pos];
	int mid = (left+right)/2;
	if(j <= mid) return segquery(2*pos,left,mid,i,j);
	if(i >= mid + 1) return segquery(2*pos+1,mid+1,right,i,j);
	return (segquery(2*pos,left,mid,i,j) | segquery(2*pos+1,mid+1,right,i,j));
}
int LCA(int u,int v){
	if(nivel[u] < nivel[v]) swap(u,v);
	for(int i = MAXL-1;i>=0;i--){
		int  p = ancestral[u][i];
		if(p != -1 && nivel[p] >= nivel[v]){
			u = p;
		}
	}
	if(u == v) return u;
	for(int i = MAXL - 1;i>=0;i--){
		if(ancestral[u][i] != ancestral[v][i] && ancestral[u][i] != -1){
			u = ancestral[u][i];
			v = ancestral[v][i];
		}
	}
	return ancestral[u][0];
}
int queryup(int u,int v){
	int ret = 0,vchain = chainId[v];
	while(true){
		int uchain = chainId[u];
		if(uchain == vchain){
			ret |= segquery(1,1,n,chainPos[v],chainPos[u]);
			break;
		}
		else{
			ret |= segquery(1,1,n,chainPos[chainHead[uchain]],chainPos[u]);
			u = chainHead[uchain];
			u = ancestral[u][0];
		}
	}
	return ret;
}
void query1(int v,int cor){
	update(1,1,n,chainPos[v], (1 << cor));
}
int query2(int u,int v){
	int p = LCA(u,v);
	int ret = (queryup(u,p) | queryup(v,p));
	return ret != 1 && __builtin_popcount(ret) == 1;
}
int main(){
	getint(n);
	for(int i = 1;i<n;i++){
		int u,v;
		getint(u);getint(v);
		u++;v++;
		grafo[u].push_back(v);
		grafo[v].push_back(u);
		memset(ancestral[i],-1,sizeof(ancestral[i]));
	}
	memset(ancestral[n],-1,sizeof(ancestral[n]));
	dfs(1,-1);
	chainNum++;
	HLD(1,-1);
	for(int i = 1;i<=n;i++) update(1,1,n,i,1);
	getint(q);
	while(q--){
		int op;
		getint(op);
		if(op == 1){
			int u,v;
			getint(u);getint(v);
			u++;
			query1(u,v);
		}
		else{
			int u,v;
			getint(u);getint(v);
			u++;v++;
			if(query2(u,v)) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}