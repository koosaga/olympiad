// Ivan Carvalho
// Solution to https://www.spoj.com/problems/POLQUERY/
#include <bits/stdc++.h>
#define gc getchar_unlocked
inline void getint(int &x){
    int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
const int MAXN = 2*1e5 + 10;
const int MAXM = 5*MAXN;
int n,m,e1[MAXM],e2[MAXM],isbridge[MAXM],low[MAXN],num[MAXN],dfsCount,treeComp,bridgeTreeId[MAXN],biconnectedId[MAXN],articulation[MAXN],blockComp;
int ini[MAXN],nivel[MAXN],seg[4*MAXN],tourVetor[MAXN],tourId;
int ini2[MAXN],nivel2[MAXN],seg2[8*MAXN],tourVetor2[2*MAXN],tourId2;
vector<int> grafo[MAXN];
vector<int> arvore[MAXN];
vector<int> blockCut[MAXN];
vector<vector<int> > perdi;
stack<int> pilha;
void get_bcc(int idx){
	vector<int> componente;
	while(!pilha.empty()){
		int davez = pilha.top();
		pilha.pop();
		componente.push_back(davez);
		if(davez == idx) break;
	}
	perdi.push_back(componente);
}
void dfs_tarjan(int v,int p){
	num[v] = low[v] = ++dfsCount;
	int children = 0;
	for(int i = 0;i<grafo[v].size();i++){
		int idx = grafo[v][i];
		int u = (e1[idx] != v) ? e1[idx] : e2[idx];
		if(u == p) continue;
		if(num[u] == 0){
			children++;
			pilha.push(idx);
			dfs_tarjan(u,v);
			if(low[u] > num[v]) isbridge[idx] = 1;
			if(low[u] >= num[v]){
				articulation[v] = 1;
				get_bcc(idx);
			}
			low[v] = min(low[v],low[u]);
		}
		else{
			low[v] = min(low[v],num[u]);
		}
	}
	if(p == -1){
		articulation[v] = (children > 1);
	}
}
void dfs_bridge(int v,int p,int compId){
	if(compId == -1) compId = ++treeComp;
	bridgeTreeId[v] = compId;
	for(int i = 0;i<grafo[v].size();i++){
		int idx = grafo[v][i];
		int u = (e1[idx] != v) ? e1[idx] : e2[idx];
		if(u == p || bridgeTreeId[u]) continue;
		if(isbridge[idx]){
			dfs_bridge(u,v,-1);
			arvore[bridgeTreeId[v]].push_back(bridgeTreeId[u]);
			arvore[bridgeTreeId[u]].push_back(bridgeTreeId[v]);
		}
		else{
			dfs_bridge(u,v,compId);
		}
	}
}
void dfs_tree(int v,int p){
	ini[v] = ++tourId;
	tourVetor[tourId] = v;
	for(int i = 0;i<arvore[v].size();i++){
		int u = arvore[v][i];
		if(u == p) continue;
		nivel[u] = nivel[v] + 1;
		dfs_tree(u,v);
		tourVetor[++tourId] = v;
	}
}
void dfs_bcc(int v,int p){
	ini2[v] = ++tourId2;
	tourVetor2[tourId2] = v;
	for(int i = 0;i<blockCut[v].size();i++){
		int u = blockCut[v][i];
		if(u == p) continue;
		nivel2[u] = nivel2[v] + 1;
		dfs_bcc(u,v);
		tourVetor2[++tourId2] = v;
	}
}
int join(int u,int v){
	if(nivel[u] < nivel[v]) return u;
	return v;
}
int join2(int u,int v){
	if(nivel2[u] < nivel2[v]) return u;
	return v;
}
void build(int pos,int left,int right){
	if(left == right){
		seg[pos] = tourVetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	seg[pos] = join(seg[2*pos],seg[2*pos+1]);
}
int query(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j) return seg[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	return join(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int LCA(int u,int v){
	return query(1,1,tourId, min(ini[u],ini[v]), max(ini[u],ini[v]) );
}
int path(int u,int v,int g1,int g2){
	if(nivel[g1] > nivel[g2]) swap(g1,g2);
	int ancestor = LCA(u,v);
	if(ancestor == g1){
		if(LCA(u,g2) == g2 || LCA(v,g2) == g2) return 0;
		return 1;
	}
	if(LCA(g1,ancestor) == ancestor && (LCA(g2,v) == g2 || LCA(g2,u) == g2)){
		return 0;
	}
	return 1;
}
void build2(int pos,int left,int right){
	if(left == right){
		seg2[pos] = tourVetor2[left];
		return;
	}
	int mid = (left+right)/2;
	build2(2*pos,left,mid);
	build2(2*pos+1,mid+1,right);
	seg2[pos] = join2(seg2[2*pos],seg2[2*pos+1]);
}
int query2(int pos,int left,int right,int i,int j){
	if(left >= i && right <= j) return seg2[pos];
	int mid = (left+right)/2;
	if(j <= mid) return query2(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query2(2*pos+1,mid+1,right,i,j);
	return join2(query2(2*pos,left,mid,i,j),query2(2*pos+1,mid+1,right,i,j));
}
int LCA2(int u,int v){
	return query2(1,1,tourId2, min(ini2[u],ini2[v]), max(ini2[u],ini2[v]) );
}
int check2(int a,int b,int c){
	int ancestral = LCA2(a,b);
	if(ancestral == c) return 0;
	int precalc = LCA2(c,ancestral);
	if(precalc != ancestral) return 1;
	if(LCA2(a,c) == c){
		return 0;
	}
	if(LCA2(b,c) == c){
		return 0;
	}
	return 1;
}
int main(){
	getint(n);getint(m);
	for(int i = 1;i<=m;i++){
		getint(e1[i]);getint(e2[i]);
		grafo[e1[i]].push_back(i);
		grafo[e2[i]].push_back(i);
	}
	dfs_tarjan(1,-1);
	for(int i = 1;i<=n;i++){
		if(articulation[i]) biconnectedId[i] = ++blockComp;
	}
	while(!perdi.empty()){
		vector<int> componente = perdi.back();
		perdi.pop_back();
		blockComp++;
		for(int pos = 0;pos<componente.size();pos++){
			int u = e1[componente[pos]],v = e2[componente[pos]];
			if(!articulation[u]) biconnectedId[u] = blockComp;
			if(!articulation[v]) biconnectedId[v] = blockComp;
			if(articulation[u]){
				blockCut[biconnectedId[u]].push_back(blockComp);
				blockCut[blockComp].push_back(biconnectedId[u]);
			}
			if(articulation[v]){
				blockCut[biconnectedId[v]].push_back(blockComp);
				blockCut[blockComp].push_back(biconnectedId[v]);
			}
		}
	}
	for(int i = 1;i<=blockComp;i++){
		sort(blockCut[i].begin(),blockCut[i].end());
		blockCut[i].erase(unique(blockCut[i].begin(),blockCut[i].end()),blockCut[i].end());
	}
	dfs_bridge(1,-1,-1);
	dfs_tree(1,-1);
	build(1,1,tourId);
	dfs_bcc(1,-1);
	build2(1,1,tourId2);
	int Q;
	getint(Q);
	while(Q--){
		int op;
		getint(op);
		if(op == 2){
			int a,b,c;
			getint(a);getint(b);getint(c);
			if(!articulation[c]){
				printf("da\n");
				continue;
			}
			a = biconnectedId[a];
			b = biconnectedId[b];
			c = biconnectedId[c];
			if(check2(a,b,c)) printf("da\n");
			else printf("ne\n");
		}
		else{
			int a,b,g1,g2;
			getint(a);getint(b);getint(g1);getint(g2);
			if(bridgeTreeId[g1] == bridgeTreeId[g2]){
				printf("da\n");
				continue;
			}
			if(bridgeTreeId[a] == bridgeTreeId[b]){
				printf("da\n");
				continue;
			}
			a = bridgeTreeId[a];
			b = bridgeTreeId[b];
			g1 = bridgeTreeId[g1];
			g2 = bridgeTreeId[g2];
			if(path(a,b,g1,g2)) printf("da\n");
			else printf("ne\n");
		}
	}
	return 0;
}