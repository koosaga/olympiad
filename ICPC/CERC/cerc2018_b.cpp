#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;
using pi = pair<int, int>;

int n, m;
pi pos[MAXN];
int ans[MAXN];
struct edg{ int s, e, x, p, q; };

struct disj{
	int pa[MAXN], rk[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] == x ? x : find(pa[x]);
	}
	bool uni(int p, int q, vector<pi> &rb){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		pa[q] = p;
		rb.emplace_back(q, -1);
		if(rk[p] == rk[q]){
			rk[p]++;
			rb.emplace_back(p, -2);
		}
		return 1;
	}
	void rollback(vector<pi> &rb){
		reverse(rb.begin(), rb.end());
		for(auto &i : rb){
			if(i.second == -1) pa[i.first] = i.first;
			else rk[i.first]--;
		}
	}
}disj;

void dnc(int s, int e, vector<edg> el, int v){
	vector<pi> rb;
	for(auto &i : el){
		if(i.s <= s && e <= i.e && i.x <= v){
			disj.uni(i.p, i.q, rb);
		}
	}
	if(s == e){
		if(disj.find(pos[s].first) == disj.find(pos[s].second)) ans[s] = v;
	}
	else{
		int m = (s+e)/2;
		vector<edg> l, r;
		for(auto &i : el){
			if(i.s <= s && e <= i.e) continue;
			if(i.s <= m) l.push_back(i);
			if(m < i.e) r.push_back(i);
		}
		dnc(s, m, l, v);
		dnc(m+1, e, r, v);
	}
	disj.rollback(rb);
}


int main(){
	map<pi, pi> mp;
	vector<edg> edge;
	int q;
	scanf("%d %d",&n,&q);
	disj.init(n);
	for(int i=0; i<q; i++){
		int t; scanf("%d",&t);
		if(t == 0){
			int x, y, v; scanf("%d %d %d",&x,&y,&v);
			if(x > y) swap(x, y);
			mp[pi(x, y)] = pi(m, v);
		}
		if(t == 1){
			int x, y; scanf("%d %d",&x,&y);
			if(x > y) swap(x, y);
			auto drog = mp[pi(x, y)];
			mp.erase(pi(x, y));
			if(drog.first < m){
				edge.push_back({drog.first, m - 1, drog.second, x, y});
			}
		}
		if(t == 2){
			int x, y; scanf("%d %d",&x,&y);
			if(x > y) swap(x, y);
			pos[m++] = pi(x, y);
		}
	}
	for(auto &i : mp){
		if(i.second.first < m){
			edge.push_back({i.second.first, m - 1, i.second.second, i.first.first, i.first.second});
		}
	}
	memset(ans, -1, sizeof(ans));
	for(int i=9; i>=0; i--){
		dnc(0, m - 1, edge, i);
	}
	for(int i=0; i<m; i++) printf("%d\n", ans[i]);
}
