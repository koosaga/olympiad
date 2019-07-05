#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
using lint = long long;
using pi = pair<int, int>;

void ass(bool p){
	if(!p){
		puts("-1");
		exit(0);
	}
}

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m;
vector<pi> gph[MAXN];

void solve(){
	map<pi, int> mp;
	scanf("%d",&n);
	int m = 0;
	int f = 0;
	int cnt = 0;
	disj.init(MAXN);
	for(int i=1; i<=n; i++){
		int x; scanf("%d",&x);
		gph[i].resize(x);
		for(auto &j : gph[i]){
			scanf("%d",&j.first);
			auto pr = pi(i, j.first);
			ass(i != j.first);
			if(pr.first > pr.second) swap(pr.first, pr.second);
			if(mp.find(pr) == mp.end()){
				mp[pr] = 2 * (cnt), cnt++;
				j.second = mp[pr];
			}
			else j.second = mp[pr] + 1;
		}
		m += x;
	}
	m /= 2;     ass(m <= 20000);
	for(int i=1; i<=n; i++){
		for(int j=0; j<gph[i].size(); j++){
			int l = gph[i][j].second ^ 1;
			int r = gph[i][(j+1)%gph[i].size()].second;
			disj.uni(l, r);
		}
	}
	for(int i=0; i<2*m; i++) if(disj.find(i) == i) f++;
    ass(n - m + f == 2);
}
	

int main(){
	int x; cin >> x;
	if(x == 1){
		solve();
	}
	else{
		int n, m;
		scanf("%d %*d %d",&n,&m);
		set<int> gph[MAXN];

		for(int i=0; i<m; i++){
			int s, e; scanf("%d %d",&s,&e);
			ass(s != e);
			ass(gph[s].find(e) == gph[s].end());
			gph[s].insert(e);
			gph[e].insert(s);
		}
		queue<int> que;
		for(int i=1; i<=n; i++){
			if(gph[i].size() == 2) que.push(i);
		}
		while(!que.empty()){
			int x = que.front(); que.pop();
			if(gph[x].size() != 2) continue;
			int p = *gph[x].begin();
			int q = *gph[x].rbegin();
			gph[p].erase(x);
			gph[q].erase(x);
			gph[x].clear();
			ass(gph[p].find(q) == gph[p].end());
			gph[p].insert(q);
			gph[q].insert(p);
			if(gph[p].size() == 2) que.push(p);
			if(gph[q].size() == 2) que.push(q);
		}
		int v = 0, e = 0;
		for(int i=0; i<=n; i++){
			if(gph[i].size()){
				v += 1;
				e += gph[i].size();
			}
		}
		if(v == 5 && e == 20){
		}
		else if(v == 6 && e == 18){
			disj.init(2*n+1);
			for(int i=1; i<=n; i++){
				for(auto &j : gph[i]){
					disj.uni(i, j + n);
					disj.uni(i + n, j);
				}
			}
			for(int i=1; i<=n; i++){
				ass(disj.find(i) != disj.find(i + n));
			}
		}
		else ass(0);
	}
    puts("1");
}
