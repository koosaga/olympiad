#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

struct qry{
	int dep;
	int s, e, x;
	int idx;
	bool operator<(const qry &q)const{
		return pi(dep, x) < pi(q.dep, q.x);
	}
};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

vector<qry> v;
vector<int> gph[MAXN];
vector<pi> w;
int lab[MAXN], par[MAXN], dep[MAXN];
int n = 1, q, r, ret[MAXN];
int din[MAXN], dout[MAXN], piv;

void dfs(int x){
	din[x] = ++piv;
	w.emplace_back(dep[x], x);
	for(auto &i : gph[x]){
		dep[i] = dep[x] + 1;
		dfs(i);
	}
	dout[x] = piv;
}

void solve(vector<pi> &V, vector<qry> &Q){
	int pnt = 0;
	for(auto &i : Q){
		while(pnt < V.size() && V[pnt].second <= i.x){
			bit.add(din[V[pnt].second], 1);
			pnt++;
		}
		ret[i.idx] += bit.query(i.e) - bit.query(i.s-1);
	}
	while(pnt > 0){
		pnt--;
		bit.add(din[V[pnt].second], -1);
	}
}

int main(){
	scanf("%d",&q);
	char buf[5];
	int r = 0;
	lab[1] = 1;
	for(int i=0; i<q; i++){
		scanf("%s", buf);
		if(*buf == 'Z'){
			int p, v;
			scanf("%d %d",&p,&v);
			n++;
			lab[p] = n;
			gph[lab[v]].push_back(lab[p]);
			dep[lab[p]] = dep[lab[v]] + 1;
		}
		else{
			int q, k;
			scanf("%d %d",&q,&k);
			q = lab[q];
			k += dep[q] +1;
			v.push_back({k, q, q, n, ++r});
		}
	}
	dfs(1);
	for(auto &i : v){
		i.s = din[i.s];
		i.e = dout[i.e];
	}
	sort(v.begin(), v.end());
	sort(w.begin(), w.end());
	int ptr = 0;
	for(int i=0; i<w.size(); ){
		int e = i;
		while(e < w.size() && w[e].first == w[i].first) e++;
		vector<pi> pnt;
		vector<qry> query;
		for(int j=i; j<e; j++){
			pnt.push_back(w[j]);
		}
		while(ptr < v.size() && v[ptr].dep == w[i].first){
			query.push_back(v[ptr++]);
		}
		i = e;
		solve(pnt, query);
	}
	for(int i=1; i<=r; i++) printf("%d\n", ret[i]);
}