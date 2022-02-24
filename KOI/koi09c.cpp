#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n, k;
vector<vector<pi>> gph;
vector<int> deg;
vector<int> ans;

pi dfs(int x, int p = -1){
	lint closest = 1e18;
	lint farthest = 0;
	for(auto &[w, y] : gph[x]){
		if(deg[y] || y == p) continue;
		auto sln = dfs(y, x);
		if(sln.first == 0){ // covered
			// closest covering ones
			closest = min(closest, sln.second + w);
		}
		else{
			if(sln.second + w > k){
				// should cover.
				ans.push_back(y);
				closest = min(closest, w);
			}
			else{
				// farthest uncovered
				farthest = max(farthest, sln.second + w);
			}
		}
	}
	if(closest + farthest <= k) return pi(0, closest);
	return pi(1, farthest);
}

vector<int> vtx, edg;

bool trial(lint x){
	k = x;
	ans.clear();
	vector<pi> intv;
	for(int i = 0; i < sz(vtx); i++){
		intv.push_back(dfs(vtx[i]));
	}
	if(sz(ans) > 2) return 0;
	vector<int> rel_pos(sz(vtx) * 2);
	vector<int> covered(sz(vtx));
	for(int i = 1; i < sz(rel_pos); i++){
		rel_pos[i] = rel_pos[i - 1] + edg[(i - 1) % sz(vtx)];
	}
	int csum = accumulate(all(edg), 0);
	for(int i = 0; i < sz(vtx); i++){
		if(intv[i].first == 0){
			for(int j = 0; j < sz(vtx); j++){
				int d = abs(rel_pos[j] - rel_pos[i]);
				d = min(d, csum - d);
				if(intv[j].first == 1) d += intv[j].second;
				if(d <= k - intv[i].second) covered[j] = 1;
			}
		}
	}
	vector<pi> v;
	for(int i = 0; i < sz(vtx); i++){
		if(covered[i] == 0){
			assert(intv[i].first == 1);
			if(sz(ans) == 2) return 0;
			int r = upper_bound(all(rel_pos), rel_pos[i] + k - intv[i].second) - rel_pos.begin() - 1;
			int l = lower_bound(all(rel_pos), rel_pos[i + sz(vtx)] - k + intv[i].second) - rel_pos.begin();
			l -= sz(vtx);
			if(r - l + 1 >= sz(vtx)) continue;
			l += sz(vtx); l %= sz(vtx);
			r += sz(vtx); r %= sz(vtx);
			v.emplace_back(l, r);
		}
	}
	if(sz(ans) == 2){
		if(sz(v)) return 0;
		return 1;
	}
	vector<int> nxt(sz(vtx) * 2, 1e9);
	for(auto &[x, y] : v){
		if(x <= y){
			nxt[x] = min(nxt[x], (int)y);
			nxt[x + sz(vtx)] = min(nxt[x + sz(vtx)], (int)y + sz(vtx));
		}
		else{
			nxt[x] = min(nxt[x], (int)y + sz(vtx));
		}
	}
	for(int i = sz(nxt) - 2; i >= 0; i--) nxt[i] = min(nxt[i], nxt[i + 1]);
	if(sz(ans) == 0){
		for(int i = 0; i < sz(vtx); i++){
			if(nxt[i + 1] >= i + sz(vtx)){
				ans.push_back(vtx[i]);
				ans.push_back(vtx[(i + 1) % sz(vtx)]);
				return 1;
			}
			int j = nxt[i + 1];
			if(nxt[j + 1] >= i + sz(vtx)){
				ans.push_back(vtx[i]);
				ans.push_back(vtx[j % sz(vtx)]);
				return 1;
			}
		}
		return 0;
	}
	if(sz(ans) == 1){
		for(int i = 0; i < sz(vtx); i++){
			if(nxt[i + 1] >= i + sz(vtx)){
				ans.push_back(vtx[i]);
				return 1;
			}
		}
		return 0;
	}
	assert(0);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	deg.resize(n);
	gph.resize(n);
	for(int i = 0; i < n; i++){
		int s, e, x; cin >> s >> e >> x;
		s--; e--;
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
		deg[s]++; deg[e]++;
	}
	{
		queue<int> que;
		for(int i = 0; i < n; i++){
			if(deg[i] == 1) que.push(i);
		}
		while(sz(que)){
			int x = que.front();
			que.pop();
			for(auto &[w, y] : gph[x]){
				if(deg[y]){
					deg[y]--;
					deg[x]--;
					if(deg[y] == 1) que.push(y);
				}
			}
		}
		for(int i = 0; i < n; i++){
			if(deg[i]){
				for(int j = i; j != -1; ){
					vtx.push_back(j);
					int nxt = -1;
					for(auto &[w, k] : gph[j]){
						if(deg[k]){
							nxt = k;
							edg.push_back(w);
						}
					}
					deg[j] = 0;
					j = nxt;
				}
				rotate(edg.begin(), edg.begin() + 1, edg.end());
				for(auto &i : vtx) deg[i] = 1;
				break;
			}
		}
	}
//	for(auto &i : vtx) cout << i << " ";
//	cout << endl;
//	for(auto &i : edg) cout << i << " ";
//	cout << endl;
	lint s = 0, e = 5e8;
	while(s != e){
		lint m = (s + e) / 2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	trial(s);
	cout << ans[0]+1 << " " << ans[1]+1 << "\n" << s << endl;
}
