#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

struct disj{
	int pa[MAXN], rk[MAXN];
	void init(int n){
		for(int i=1; i<=n; i++){
			pa[i] = i;
			rk[i] = 0;
		}
	}
	int find(int x){
		return pa[x] == x ? x : find(pa[x]);
	}
	bool uni(int p, int q, vector<pi> &v){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		if(rk[p] < rk[q]) swap(p, q);
		v.push_back({1, q});
		pa[q] = p;
		if(rk[p] == rk[q]){
			rk[p]++;
			v.push_back({2, p});
		}
		return true;
	}
	void revert(vector<pi> &v){
		reverse(v.begin(), v.end());
		for(auto &i : v){
			if(i.first == 1) pa[i.second] = i.second;
			else rk[i.second]--;
		}
	}
}disj;

struct qry{ int s, e, x; };

int n, m, q;
int st[MAXN], ed[MAXN], cost[MAXN], chk[MAXN];
pi qr[MAXN];
vector<qry> ans[2005];

bool cmp(int &a, int &b){ return pi(cost[a], a) < pi(cost[b], b);}

void contract(int s, int e, vector<int> v, vector<int> &must_mst, vector<int> &maybe_mst){
	sort(v.begin(), v.end(), cmp);
	vector<pi> snapshot;
	for(int i=s; i<=e; i++) disj.uni(st[qr[i].first], ed[qr[i].first], snapshot);
	for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) must_mst.push_back(i);
	disj.revert(snapshot);
	for(auto &i : must_mst) disj.uni(st[i], ed[i], snapshot);
	for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) maybe_mst.push_back(i);
	disj.revert(snapshot);
}

vector<pi> gph[2005];

bool dfs(int x, int p, int e, int v){
	if(x == e) return true;
	for(auto &i : gph[x]){
		if(i.first == p) continue;
		if(i.second <= v && dfs(i.first, x, e, v)) return true;
	}
	return false;
}

void solve(int s, int e, vector<int> v, vector<int> mst){
	if(s == e){
		cost[qr[s].first] = qr[s].second;
		int idx = qr[s].first;
		for(auto &i : v){
			if(cost[idx] > cost[i]) idx = i;
		}
		if(st[idx] != ed[idx]){
			gph[st[idx]].push_back(pi(ed[idx], cost[idx]));
			gph[ed[idx]].push_back(pi(st[idx], cost[idx]));
		}
		for(auto &i : mst){
			gph[st[i]].push_back(pi(ed[i], cost[i]));
			gph[ed[i]].push_back(pi(st[i], cost[i]));
		}
		for(auto &i : ans[s]){
			if(dfs(i.s, -1, i.e, i.x)){
				puts("1");
			}
			else puts("0");
		}
		for(int i=1; i<=n; i++) gph[i].clear();
		return;
	}
	int m = (s+e)/2;
	vector<int> lv = v, rv = v;
	vector<int> must_mst, maybe_mst;
	for(int i=m+1; i<=e; i++){
		chk[qr[i].first]--;
		if(chk[qr[i].first] == 0) lv.push_back(qr[i].first);
	}
	vector<pi> snapshot;
	contract(s, m, lv, must_mst, maybe_mst);
	vector<int> lmst = mst;
	for(auto &i : must_mst){
		disj.uni(st[i], ed[i], snapshot);
		lmst.push_back(i);
	}
	solve(s, m, maybe_mst, lmst);
	disj.revert(snapshot);
	must_mst.clear(); maybe_mst.clear();
	for(int i=m+1; i<=e; i++) chk[qr[i].first]++;
	for(int i=s; i<=m; i++){
		chk[qr[i].first]--;
		if(chk[qr[i].first] == 0) rv.push_back(qr[i].first);
	}
	contract(m+1, e, rv, must_mst, maybe_mst);
	vector<int> rmst = mst;
	for(auto &i : must_mst){
		rmst.push_back(i);
		disj.uni(st[i], ed[i], snapshot);
	}
	solve(m+1, e, maybe_mst, rmst);
	disj.revert(snapshot);
	for(int i=s; i<=m; i++) chk[qr[i].first]++;
}

int main(){
	while(true){
		scanf("%d %d",&n,&m);
		if(n == 0 && m == 0) break;
		vector<int> ve;
		for(int i=0; i<m; i++){
			scanf("%d %d %d",&st[i],&ed[i],&cost[i]);
			cost[i] *= -1;
		}
		scanf("%d",&q);
		qr[0].first = 0;
		qr[0].second = cost[0];
		char buf[5];
		int cnt = 0;
		for(int i=1; i<=q; i++){
			scanf("%s", buf);
			if(*buf == 'S'){
				int s, e, x;
				scanf("%d %d %d",&s,&e,&x);
				ans[cnt].push_back({s, e, -x});
			}
			else{
				cnt++;
				int x, y;
				scanf("%d %d",&x,&y);
				qr[cnt] = pi(x-1, -y);
				chk[x-1]++;
			}
		}
		q = cnt + 1;
		disj.init(n);
		for(int i=0; i<m; i++) if(!chk[i]) ve.push_back(i);
		solve(0, q-1, ve, vector<int>());
		for(int i=0; i<q; i++) ans[i].clear();
		memset(chk, 0, sizeof(chk));
	}
}
