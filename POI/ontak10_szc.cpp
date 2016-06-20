#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
 
int n, a[100005];
int m, q;
 
vector<int> v;
 
struct edge{
	int s, e, x;
}edg[500005];
 
struct query{
	int pos, x, k, idx;
}qry[500005];
 
int ret[500005];
 
struct node{
	int ls, rs;
	int sum;
	node(){
		ls = rs = 0;
		sum = 0;
	}
}tree[9000005];
 
int piv;
 
void add(int pos, int ps, int pe, int p){
	tree[p].sum++;
	if(ps == pe) return;
	int pm = (ps+pe)/2;
	if(pos <= pm){
		if(!tree[p].ls) tree[p].ls = ++piv;
		add(pos, ps, pm, tree[p].ls);
	}
	else{
		if(!tree[p].rs) tree[p].rs = ++piv;
		add(pos, pm+1, pe, tree[p].rs);
	}
}
 
int kth(int ps, int pe, int k, int p){
	if(ps == pe) return ps;
	int pm = (ps + pe) / 2;
	int cnt = (tree[p].ls ? tree[tree[p].ls].sum : 0);
	if(cnt >= k){
		return kth(ps, pm, k, tree[p].ls);
	}
	else return kth(pm+1, pe, k - cnt, tree[p].rs);
}
 
void dfs(int ps, int pe, int prev, int cur){
	if(ps == pe){
		while(tree[prev].sum){
			tree[prev].sum--;
			add(ps, 1, n, cur);
		}
		return;
	}
	int pm = (ps + pe) / 2;
	if(tree[prev].ls){
		dfs(ps, pm, tree[prev].ls, cur);
	}
	if(tree[prev].rs){
		dfs(pm+1, pe, tree[prev].rs, cur);
	}
}
 
struct disj{
	int pa[100005], sz[100005];
	void init(int n, int *a){
		piv = n;
		for(int i=1; i<=n; i++){
			sz[i] = 1;  
			pa[i] = i;
			add(a[i],1,n,i);
		}
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return;
		if(sz[p] < sz[q]){
			swap(p, q);
		}
		dfs(1, n, q, p);
		pa[q] = p;
		sz[p] += sz[q];
		find(q);
	}
}disj;
 
bool cmp1(edge a, edge b){return a.x < b.x;}
bool cmp2(query a, query b){return a.x < b.x;}
 
int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&edg[i].s,&edg[i].e,&edg[i].x);
	}
	for(int i=0; i<q; i++){
		scanf("%d %d %d",&qry[i].pos,&qry[i].x,&qry[i].k);
		qry[i].idx = i;
	}
	v.push_back(-1e9);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=1; i<=n; i++){
		a[i] = (int)(lower_bound(v.begin(), v.end(), a[i]) - v.begin());
	}
	sort(edg,edg+m,cmp1);
	sort(qry,qry+q,cmp2);
	memset(ret,-1,sizeof(ret));
	disj.init(n, a);
	int p = 0;
	for(int i=0; i<q; i++){
		while(p < m && edg[p].x <= qry[i].x){
			disj.uni(edg[p].s, edg[p].e);
			p++;
		}
		int pt = disj.find(qry[i].pos);
		if(disj.sz[pt] < qry[i].k) continue;
		ret[qry[i].idx] = v[kth(1, n, disj.sz[pt] - qry[i].k + 1, pt)];
	}
	for(int i=0; i<q; i++){
		printf("%d\n",ret[i]);
	}
}