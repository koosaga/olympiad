#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;

vector<int> gph[MAXN];
int n, m, r[2], dist[2][MAXN];
int a[MAXN], par[MAXN];
pi dp[MAXN];

void dfs_far(int x, int p){
	par[x] = p;
	dp[x] = pi(0, x);
	for(auto &i : gph[x]){
		if(i != p){
			dfs_far(i, x);
			dp[x] = max(dp[x], pi(dp[i].first + 1, i));
		}
	}
}

struct jaryoguzo{
	vector<int> v;
	int mark[MAXN];
	int cnt[MAXN], nonZeroes;
	void upd(int x, int v){
		if(cnt[x] > 0) nonZeroes--;
		cnt[x] += v;
		if(cnt[x] > 0) nonZeroes++;
	}
	void push_back(int x){
		v.push_back(x);
		upd(x, +1);
	}
	void pop_back(){
		upd(v.back(), -1);
		v.pop_back();
	}
	void mark_interval(int s, int e, int d){
		for(int i=s; i<e && i<v.size(); i++){
			if(mark[v.size() - 1 - i] == 0) upd(v[v.size() - 1 - i], -1);
			mark[v.size()-1-i] += d;
			if(mark[v.size() - 1 - i] == 0) upd(v[v.size() - 1 - i], +1);
		}
	}
	int query(){ return nonZeroes; }
}JG;

int ret[MAXN];

void dfs_calc(int x, int p){
	vector<int> pth, sndmax;
	for(int j=x; ; j=dp[j].second){
		int smax = 0;
		for(auto &k : gph[j]){
			if(k != par[j] && k != dp[j].second){
				smax = max(smax, dp[k].first + 1); 
			}
		}
		pth.push_back(j);
		sndmax.push_back(smax);
		if(j == dp[j].second) break;
	}
	int pointer = (int)pth.size() - 1;
	JG.mark_interval(0, pointer, +1);
	for(int i = 0; i < pth.size(); i++){
		ret[pth[i]] = JG.query();
		JG.push_back(a[pth[i]]);
		for(auto &j : gph[pth[i]]){
			if(j != par[pth[i]] && dp[pth[i]].second != j){
				dfs_calc(j, pth[i]);
			}
		}
		pointer += 1;
		if(i + 1 < pth.size()) JG.mark_interval(0, 1, +1);
		if(i + 1 < pth.size()) JG.mark_interval(pointer - 2 * i - 2, pointer - 2 * i, -1);
		if(i + 1 < pth.size()) JG.mark_interval(1, 1 + sndmax[i], +1);
	}
	for(int i = (int)pth.size() - 1; i >= 0; i--){
		if(i + 1 < pth.size()) JG.mark_interval(1, 1 + sndmax[i], -1);
		if(i + 1 < pth.size()) JG.mark_interval(pointer - 2 * i - 2, pointer - 2 * i, +1);
		if(i + 1 < pth.size()) JG.mark_interval(0, 1, -1);
		pointer -= 1;
		JG.pop_back();
	}
	JG.mark_interval(0, pointer, -1);
}

vector<int> solve(int r){
	dfs_far(r, -1);
	dfs_calc(r, -1);
	return vector<int>(ret + 1, ret + n + 1);
}

void fill_dist(int x, int p, int d, int l){
	dist[l][x] = d;
	for(auto &i : gph[x]){
		if(i != p){
			fill_dist(i, x, d + 1, l);
		}
	}
}

pi dfs(int x, int p){
	pi ret(0, x);
	for(auto &i : gph[x]){
		if(i != p){
			auto y = dfs(i, x);
			y.first++;
			ret = max(ret, y);
		}
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	r[0] = dfs(1, 0).second;
	r[1] = dfs(r[0], 0).second;
	fill_dist(r[0], -1, 0, 0);
	fill_dist(r[1], -1, 0, 1);
	auto v1 = solve(r[0]);
	auto v2 = solve(r[1]);
	for(int i=1; i<=n; i++){
		if(dist[0][i] <= dist[1][i]) printf("%d\n", v2[i-1]);
		else printf("%d\n", v1[i-1]);
	}
}
