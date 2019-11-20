#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 800005;

struct edge{
	int s, e, x;
	bool operator<(const edge &ed)const{
		return pi(s, -e) < pi(ed.s, -ed.e);
	}
};

struct disj{
	int pa[MAXN], msk[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	void set(int x, int y){
		msk[find(x)] |= (1<<y);
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; msk[p] |= msk[q]; return 1;
	}
}disj;

void ass(bool p, string msg){
	if(!p){
		cout << msg << endl;
		exit(0);
	}
}

vector<edge> edg;
vector<pi> gph[MAXN];

int n;
void solve(){
	int cnt = 0;
	disj.init(sz(edg)*2);
	for(auto &i : edg){
		disj.set(cnt, i.x-1);
		disj.set(cnt+1, i.x-1);
		gph[i.s].emplace_back(i.e, cnt++);
		gph[i.e].emplace_back(i.s, cnt++);
	}
	for(int i=1; i<=n; i++){
		sort(all(gph[i]), [&](pi x, pi y){
			bool p1 = (x.first > i);
			bool p2 = (y.first > i);
			if(p1 != p2) return p1 < p2;
			return x > y;
		});
		for(int j=0; j<sz(gph[i]); j++){
			int x1 = gph[i][j].second ^ 1;
			int x2 = gph[i][(j+1)%sz(gph[i])].second;
			disj.uni(x1, x2);
		}
	}
	for(int i=0; i<2*sz(edg); i++){
		int x = edg[i/2].s;
		int y = edg[i/2].e;
		if(i & 1) swap(x, y);
		if((y - x + n) % n == n - 1) continue;
		if(disj.find(i) == i){
			ass(disj.msk[i] == 7, "neispravno bojenje");
		}
	}
	puts("tocno");
}

void add_edge(int x, int y, int z){
	if(x > y) swap(x, y); 
	edg.push_back({x, y, z});
}

int main(){
	scanf("%*d %d",&n);
	char buf[MAXN];
	scanf("%s", buf);
	for(int i=0; i<n; i++){
		add_edge(i, (i+1)%n, buf[i] - '0');
	}
	for(int i=0; i<n-3; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		add_edge(s-1, e-1, x);
	}
	sort(all(edg));
	for(int i=1; i<sz(edg); i++){
		ass(pi(edg[i-1].s, edg[i-1].e) != pi(edg[i].s, edg[i].e), "neispravna triangulacija");
	}
	vector<edge> stk;
	for(int i=0; i<sz(edg); i++){
		while(!stk.empty() && stk.back().e < edg[i].e){
			ass(stk.back().e <= edg[i].s, "neispravna triangulacija");
			stk.pop_back();
		}
		stk.push_back(edg[i]);
	}
	solve();
}
