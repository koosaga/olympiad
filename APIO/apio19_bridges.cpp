#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int B = 800;
using lint = long long;
using pi = pair<int, int>;

int n, m, q;
bool in_must[MAXN];
bool in_quer[MAXN];

struct disj{
	int pa[MAXN];
	int sz[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
		fill(sz, sz + n + 1, 1);
	}
	int find(int x){
		return pa[x] == x ? x : find(pa[x]);
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(sz[p] < sz[q]) swap(p, q);
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
	bool uni(int p, int q, vector<pi> &rvt){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(sz[p] < sz[q]) swap(p, q);
		rvt.emplace_back(q, -1);
		pa[q] = p;
		rvt.emplace_back(p, sz[p]);
		sz[p] += sz[q];
		return 1;
	}
	void revert(vector<pi> &v){
		reverse(v.begin(), v.end());
		for(auto &i : v){
			if(i.second == -1) pa[i.first] = i.first;
			else sz[i.first] = i.second;
		}
		v.clear();
	}
	int getSz(int x){ return sz[find(x)]; }
}disj;

struct edg{
	int s, e, x, idx;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
}e[MAXN];

struct qry{
	int pos, idx, thres;
	bool operator<(const qry &q)const{
		return thres < q.thres;
	}
};

int t[MAXN], x[MAXN], y[MAXN];
int rev[MAXN], ret[MAXN];
int aux[MAXN];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&e[i].s,&e[i].e,&e[i].x);
		e[i].x = 1696969696 - e[i].x;
		e[i].idx = i + 1;
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		scanf("%d %d %d",&t[i],&x[i],&y[i]);
		y[i] = 1696969696 - y[i];
	}
	sort(e, e + m);
	for(int i=0; i<q; i+=B){
		for(int i=0; i<m; i++) rev[e[i].idx] = i;
		memset(in_must, 0, sizeof(in_must));
		vector<int> must;
		vector<int> maybe;
		disj.init(n);
		for(int j=i; j<i+B && j<q; j++){
			if(t[j] == 1){
				int pos = rev[x[j]];
				in_quer[pos] = 1;
			}
		}
		for(int i=0; i<m; i++){
			if(in_quer[i]) continue;
			if(disj.uni(e[i].s, e[i].e)){
				must.push_back(i);
			}
		}
		vector<qry> qr;
		vector<int> drog;
		for(int j=i; j<i+B && j<q; j++){
			if(t[j] == 2){
				qr.push_back({x[j], j, y[j]});
			}
			if(t[j] == 1){
				if(in_quer[rev[x[j]]]){
					in_quer[rev[x[j]]] = 0;
					drog.push_back(x[j]);
				}
			}
		}
		sort(qr.begin(), qr.end());
		disj.init(n);
		int ptr = 0;
		for(auto &k : qr){
			while(ptr < must.size() && e[must[ptr]].x <= k.thres){
				disj.uni(e[must[ptr]].s, e[must[ptr]].e);
				ptr++;
			}
			vector<pi> logs;
			for(int j=i; j<k.idx; j++){
				if(t[j] == 1){
					aux[x[j]] = y[j];
				}
			}
			for(auto &i : maybe){
				if(e[i].x <= k.thres){
					disj.uni(e[i].s, e[i].e, logs);
				}
			}
			for(auto &i : drog){
				int pos = rev[i];
				int cost = aux[i];
				if(cost == 0) cost = e[pos].x;
				if(cost <= k.thres){
					disj.uni(e[pos].s, e[pos].e, logs);
				}
			}
			ret[k.idx] = disj.getSz(k.pos);
			disj.revert(logs);
			for(int j=i; j<k.idx; j++){
				if(t[j] == 1){
					aux[x[j]] = 0;
				}
			}
		}
		for(int j=i; j<q && j<i+B; j++){
			if(t[j] == 1) aux[x[j]] = y[j];
		}
		vector<edg> l, r;
		for(int i=0; i<m; i++){
			if(aux[e[i].idx]){
				e[i].x = aux[e[i].idx];
				aux[e[i].idx] = 0;
				r.push_back(e[i]);
			}
			else l.push_back(e[i]);
		}
		sort(r.begin(), r.end());
		merge(l.begin(), l.end(), r.begin(), r.end(), e);
	}
	for(int i=0; i<q; i++) if(t[i] == 2) printf("%d\n", ret[i]);
}
