// Ivan Carvalho
// Solution to https://www.spoj.com/problems/QTREE4/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
const int MAXL = 19;
const int NEG = -1e9;
inline ii join(ii A,ii B){
	return max(max(A,B), max(ii(A.first,B.first),ii(B.first,A.first)) );
}
struct seg_i{
	vector<int> seg;
	int tam;
	int delta;
	void build(int t,int d){
		tam = t;
		delta = d;
		seg.assign(2*(1 << (int)ceil(log(t)/log(2)))+2,NEG);
	}
	void update(int pos,int left,int right,int x,int val){
		if(left == right){
			seg[pos] = val;
			return;
		}
		int mid = (left+right)/2;
		if(x <= mid) update(2*pos,left,mid,x,val);
		else update(2*pos+1,mid+1,right,x,val);
		seg[pos] = max(seg[2*pos],seg[2*pos+1]);
	}
	int query(int pos,int left,int right,int i,int j){
		if(left >= i && right <= j) return seg[pos];
		int mid = (left+right)/2;
		if(j <= mid) return query(2*pos,left,mid,i,j);
		else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
		return max(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
	}
	void doUpdate(int x,int val){
		update(1,1,tam,x - delta,val);
	}
	int doQuery(int i,int j){
		return query(1,1,tam,i - delta, j - delta);
	}
};
struct seg_p{
	vector<ii> seg;
	int delta;
	int tam;
	void build(int t,int d){
		tam = t;
		delta = d;
		seg.assign(4*t + 4,ii(NEG,NEG));
	}
	void update(int pos,int left,int right,int x,ii val){
		if(left == right){
			seg[pos] = val;
			return;
		}
		int mid = (left+right)/2;
		if(x <= mid) update(2*pos,left,mid,x,val);
		else update(2*pos+1,mid+1,right,x,val);
		seg[pos] = join(seg[2*pos],seg[2*pos+1]);
	}
	ii query(int pos,int left,int right,int i,int j){
		if(left >= i && right <= j) return seg[pos];
		int mid = (left+right)/2;
		if(j <= mid) return query(2*pos,left,mid,i,j);
		else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
		return join(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
	}
	void doUpdate(int x,int val){
		update(1,1,tam,x - delta,ii(val,NEG));
	}
	ii doQuery(int i,int j){
		return query(1,1,tam,i - delta,j - delta);
	}
 
};
seg_i globaltree,filhos[MAXN];
seg_p combinacoes[MAXN];
vector<ii> grafo[MAXN];
vector<int> ctree[MAXN];
int sz[MAXN],dist[MAXN][MAXL],ancestral[MAXN][MAXL],profundidade[MAXN],ini[MAXN],fim[MAXN],block[MAXN],cor[MAXN],num,cptr,raiz,n,q,total,conversao[MAXN];
int dfs1(int v,int p){
	sz[v] = 1;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		if(u == p || block[u]) continue;
		sz[v] += dfs1(u,v);
	}
	return sz[v];
}
void dfs2(int v,int p,ii &resp){
	int mx = num - sz[v];
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		if(u == p || block[u]) continue;
		dfs2(u,v,resp);
		mx = max(mx,sz[u]);
	}
	if(mx < resp.first) resp = ii(mx,v);
}
void dfs3(int v,int p,int depth,int craiz){
	profundidade[v]++;
	ancestral[v][profundidade[v]] = craiz;
	dist[v][profundidade[v]] = depth;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first, w = grafo[v][i].second;
		if(u == p || block[u]) continue;
		dfs3(u,v,depth+w,craiz);
	}
}
int find_centroid(int v){
	num = dfs1(v,-1);
	ii resp = ii(MAXN,MAXN);
	dfs2(v,-1,resp);
	v = resp.second;
	dfs3(v,-1,0,v);
	return v;
}
int decompoe(int v){
	v = find_centroid(v);
	block[v] = 1;
	for(int i = 0;i<grafo[v].size();i++){
		int u = grafo[v][i].first;
		if(block[u]) continue;
		u = decompoe(u);
		ctree[u].push_back(v);
		ctree[v].push_back(u);
	}
	return v;
}
void dfs_ctree(int v,int p){
	ini[v] = ++cptr;
	int meuptr = 1;
	for(int i = 0;i<ctree[v].size();i++){
		int u = ctree[v][i];
		if(u == p) continue;
		conversao[u] = ++meuptr;
		dfs_ctree(u,v);
	}
	fim[v] = cptr;
	filhos[v].build(fim[v] - ini[v] + 1,ini[v] - 1);
	combinacoes[v].build(meuptr,0);
}
inline int adiciona(ii A){return A.first + A.second;}
void insert(int original){
	filhos[original].doUpdate(ini[original],0);
	combinacoes[original].doUpdate(1,0);
	globaltree.doUpdate(ini[original],adiciona(combinacoes[original].seg[1]));
	for(int depth = profundidade[original]-1;depth>=0;depth--){
		int davez = ancestral[original][depth];
		int anterior = ancestral[original][depth+1];
		int velho = adiciona(combinacoes[davez].seg[1]);
		filhos[davez].doUpdate(ini[original],dist[original][depth]);
		combinacoes[davez].doUpdate(conversao[anterior],filhos[davez].doQuery(ini[anterior],fim[anterior]));
		int novo = adiciona(combinacoes[davez].seg[1]);
		if(velho != novo) globaltree.doUpdate(ini[davez], adiciona(combinacoes[davez].seg[1]) );
	}
}
void remove(int original){
	filhos[original].doUpdate(ini[original],NEG);
	combinacoes[original].doUpdate(1,NEG);
	globaltree.doUpdate(ini[original],adiciona(combinacoes[original].seg[1]));
	for(int depth = profundidade[original]-1;depth>=0;depth--){
		int davez = ancestral[original][depth];
		int anterior = ancestral[original][depth+1];
		int velho = adiciona(combinacoes[davez].seg[1]);
		filhos[davez].doUpdate(ini[original],NEG);
		combinacoes[davez].doUpdate(conversao[anterior],filhos[davez].doQuery(ini[anterior],fim[anterior]));
		int novo = adiciona(combinacoes[davez].seg[1]);
		if(velho != novo) globaltree.doUpdate(ini[davez], adiciona(combinacoes[davez].seg[1]) );
	}
}
int main(){
	scanf("%d",&n);
	globaltree.build(n,0);
	for(int i = 1;i<=n;i++) profundidade[i] = -1;
	for(int i = 1;i<n;i++){
		int u,v,w;
		scanf("%d %d %d",&u,&v,&w);
		grafo[u].push_back(ii(v,w));
		grafo[v].push_back(ii(u,w));
	}
	int raiz = decompoe(1);
	dfs_ctree(raiz,-1);
	for(int i = 1;i<=n;i++){
		insert(i);
		cor[i] = 1;
		total++;
	}
	scanf("%d",&q);
	while(q--){
		char op;
		scanf(" %c",&op);
		if(op == 'A'){
			if(total == 0){
				printf("They have disappeared.\n");
			}
			else{
				printf("%d\n",max(0, globaltree.seg[1] ));
			}
		}
		else{
			int i;
			scanf("%d",&i);
			if(cor[i] == 0){
				cor[i] = 1;
				total++;
				insert(i);
			}
			else{
				cor[i] = 0;
				total--;
				remove(i);
			}
		}
	}
	return 0;
}