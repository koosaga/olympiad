#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
typedef pair<int,int> pi;

struct edg{int s,e,x;};
vector<edg> edges;

struct disj{
	int pa[1005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p), q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m;
int pa[1005], pe[1005];
vector<pi> graph[1005];

bool dfs(int x, int d, int p){
	if(x == d) return 1;
	for(int i=0; i<graph[x].size(); i++){
		pi e = graph[x][i];
		if(e.second == p) continue;
		if(dfs(e.second, d, x)){
			pa[e.second] = x;
			pe[e.second] = i;
			return 1;
		}
	}
	return 0;
}

vector<pi> intv;

void eraser(int piv, int pt){
	if(pt >= graph[piv].size()) return;
	for(int i=pt; i<graph[piv].size()-1; i++){
		graph[piv][i] = graph[piv][i+1];
	}
	graph[piv].pop_back();
}

struct rtree{
	vector<pi> tree[270000];
	vector<lint> psum[270000];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=0; i<=2*lim; i++){
			tree[i].clear();
			psum[i].clear();
		}
	}
	void add(int x, int v, int w){
		x += lim;
		while(x >= 1){
			tree[x].push_back(pi(v, w));
			x >>= 1;
		}
	}
	void mm(){
		for(int i=1; i<=2*lim; i++){
			sort(tree[i].begin(), tree[i].end());
			psum[i].resize(tree[i].size());			
			for(int j=0; j<tree[i].size(); j++){
				psum[i][j] = (j ? psum[i][j-1] : 0) + tree[i][j].second;
			}
		}
	}
	lint q(int s, int e, int l){
		// first <= l, second sum
		s += lim;
		e += lim;
		lint ret = 0;
		while(s < e){
			if(s%2 == 1){
				int pos = (int)(upper_bound(tree[s].begin(), tree[s].end(), pi(l, 1e9)) - tree[s].begin()) - 1;
				ret += (pos >= 0 ? psum[s][pos] : 0);
				s++;
			}
			if(e%2 == 0){
				int pos = (int)(upper_bound(tree[e].begin(), tree[e].end(), pi(l, 1e9)) - tree[e].begin()) - 1;
				ret += (pos >= 0 ? psum[e][pos] : 0);
				e--;
			}
			s >>= 1;
			e >>= 1;
		}
		if(s == e){
			int pos = (int)(upper_bound(tree[e].begin(), tree[e].end(), pi(l, 1e9)) - tree[e].begin()) - 1;
			ret += (pos >= 0 ? psum[e][pos] : 0);
			e--;
		}
		return ret;
	}
}rtree;

vector<int> poses;

void solve(){
	poses.clear();
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int x, y, w;
		scanf("%d %d %d",&x,&y,&w);
		edges.push_back({x,y,w});
	}
	disj.init(n);
	sort(edges.begin(), edges.end(), [&](const edg &a, const edg &b){return a.x < b.x;});
	for(auto &i : edges){
		if(disj.uni(i.s,i.e) == 0){
			dfs(i.s, i.e, -1);
			int pos = i.e;
			int minv = 1e9, minp = pos;
			while(pos != i.s){
				if(minv > graph[pa[pos]][pe[pos]].first){
					minv = graph[pa[pos]][pe[pos]].first;
					minp = pos;
				}
				pos = pa[pos];
			}
			int rev = -1;
			for(int i=0; i<graph[minp].size(); i++){
				if(graph[minp][i].second == pa[minp]){
					rev = i;
					break;
				}
			}
			if(rev != -1) eraser(minp, rev);
			eraser(pa[minp], pe[minp]);
			intv.push_back(pi(minv, i.x));
		}
		else{
			intv.push_back(pi(-1, i.x));
		}
		graph[i.s].push_back(pi(i.x, i.e));
		graph[i.e].push_back(pi(i.x, i.s));
	}
	rtree.init(m);
	for(auto &i : intv){
		poses.push_back(i.second);
	}
	sort(poses.begin(), poses.end());
	poses.resize(unique(poses.begin(), poses.end()) - poses.begin());
	for(auto &i : intv){
		i.second = (int)(lower_bound(poses.begin(), poses.end(), i.second)- poses.begin());
		rtree.add(i.second, i.first, poses[i.second]);
	}
	rtree.mm();
	int q;
	scanf("%d",&q);
	lint prev = 0;
	while(q--){
		lint s, e;
		scanf("%lld %lld",&s,&e);
		s -= prev, e -= prev;
		int ps = (int)(lower_bound(poses.begin(), poses.end(), (int)s) - poses.begin());
		int pe = (int)(lower_bound(poses.begin(), poses.end(), (int)e + 1) - poses.begin()) - 1;
		lint ret = rtree.q(ps, pe, s-1); // [i.first <= s-1, i.second] in gugan [ps, pe];
		printf("%lld\n",ret);
		prev = ret;
	}
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
		for(int i=0; i<=n; i++){
			graph[i].clear();
		}
		edges.clear();
		intv.clear();
	}
}