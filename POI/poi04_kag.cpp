#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 10005;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub){ return uniform_int_distribution<lint>(lb, ub)(rng); }

vector<lint> rnd;
vector<lint> hval;
vector<set<int>> gph;
map<lint, set<int>> mp;
int pa[MAXN];

int find(int x){
	return pa[x] = (pa[x] == x ? x : find(pa[x]));
}

bool solve(){
	int n, m;
	mp.clear();
	scanf("%d %d",&n,&m);
	rnd.clear(); hval.clear(); gph.clear();
	rnd.resize(n); hval.resize(n); gph.resize(n);
	iota(pa, pa + n, 0);
	for(int i=0; i<m;i++){
		int x, y; scanf("%d %d",&x,&y);
		x--; y--;
		gph[x].insert(y);
		gph[y].insert(x);
	}
	for(int i=0; i<n; i++){
		rnd[i] = randint(0, (1ll << 63) - 1);
	}
	queue<pi> que;
	for(int i=0; i<n; i++){
		hval[i] = 0;
		for(auto &j : gph[i]){
			hval[i] ^= rnd[j];
		}
		if(sz(mp[hval[i]]) > 0){
			int j = *mp[hval[i]].begin();
			que.emplace(i, j);
		}
		mp[hval[i]].insert(i);
	}
	for(int i=0; i<n; i++){
		for(auto &j : gph[i]){
			if((hval[i] ^ rnd[i]) == (hval[j] ^ rnd[j])){
				que.emplace(i, j);
			}
		}
	}
	while(sz(que)){
		int x, y;
		tie(x, y) = que.front();
		que.pop();
		x = find(x); y = find(y);
		if(x == y) continue;
		if(gph[x].find(y) != gph[x].end() && (hval[x] ^ rnd[x]) != (hval[y] ^ rnd[y])){
			continue;
		}
		if(gph[x].find(y) == gph[x].end() && hval[x] != hval[y]){
			continue;
		}
		mp[hval[x]].erase(x);
//		printf("%d %d\n", x, y);
		if(gph[x].find(y) != gph[x].end()){
			gph[x].erase(y);
			gph[y].erase(x);
			hval[x] = 0;
			mp[hval[y]].erase(y);
			hval[y] ^= rnd[x];
			if(sz(mp[hval[y]]) > 0){
				int j = *mp[hval[y]].begin();
				que.emplace(y, j);
			}
			mp[hval[y]].insert(y);
		}
		assert(gph[x] == gph[y]);
		pa[x] = y;
		for(auto &i: gph[x]){
			assert(find(i) == i);
			gph[i].erase(x);
			mp[hval[i]].erase(i);
			hval[i] ^= rnd[x];
			if(sz(mp[hval[i]]) > 0){
				int j = *mp[hval[i]].begin();
				que.emplace(i, j);
			}
			if((hval[i] ^ rnd[i]) == (hval[y] ^ rnd[y])){
				que.emplace(i, y);
			}
			mp[hval[i]].insert(i);
		}
		gph[x].clear();
	}
	int cnt = 0;
	for(int i=0; i<n; i++){
		if(find(i) == i) cnt++;
	}
	return cnt == 1;
}

int main(){
	int t; scanf("%d",&t);
	while(t--) puts(solve() ? "TAK" : "NIE");
}
