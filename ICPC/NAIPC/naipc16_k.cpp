#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

struct cht{
	pi v[200005];
	pi aux[200005];
	pi h[205];
    int sv, sh;
	void clear() {
		sv = sh = 0;
	}
	void make(){
		sort(h, h + sh);
		merge(v, v + sv, h, h + sh, aux);
		int t = sh + sv;
		sh = 0;
		sv = 0;
		for(int i=0; i<t; i++){
			if(sv && v[sv-1].first == aux[i].first) continue;
			v[sv] = aux[i];
			while(sv >= 2 && (v[sv-1].second - v[sv-2].second) * (v[sv-1].first - v[sv].first) <=
					(v[sv].second - v[sv-1].second) * (v[sv-2].first - v[sv-1].first)){
				v[sv-1] = v[sv];
				sv--;
			}
			sv++;
		}
	}
	void add(lint x, lint y){
		if(sh == 200) make();
		h[sh++] = pi(x, y);
	}
	lint query(lint x){
		lint ret = 3e18;
		if(sv){
			int s = 0, e = sv - 1;
			while(s != e){
				int m = (s+e)/2;
				if(v[m].first * x + v[m].second < v[m+1].first * x + v[m+1].second) e = m;
				else s = m+1;
			}
			ret = min(ret, v[s].first * x + v[s].second);
		}
		for(int i=0; i<sh; i++) ret = min(ret, h[i].first * x + h[i].second);
		return ret;
	}
}cht;

int n, p[200005];
lint ans[200005];

int vis[200005], sz[200005], msz[200005];
vector<pi> sub;
vector<pi> gph[200005];

void dfs(int x, int p, lint l, int c){
	if(vis[x]) return;
	sub.push_back(pi(l, x));
	for(auto &i : gph[x]){
		if(i.second != p) dfs(i.second, x, l + i.first, c);
	}
}

vector<int> dfn;
vector<vector<pi> > lis;

void dfs2(int x, int p){
	sz[x] = 1;
	msz[x] = 0;
	dfn.push_back(x);
	for(auto &i : gph[x]){
		if(i.second != p && !vis[i.second]){
			dfs2(i.second, x);
			sz[x] += sz[i.second];
			msz[x] = max(msz[x], sz[i.second]);
		}
	}
}

int get_center(int x){
	dfs2(x, -1);
	pi ans(2e9, 2e9);
	for(auto &i : dfn){
		int w = max(msz[i], (int)dfn.size() - sz[i]);
		ans = min(ans, pi(w, i));
	}
	dfn.clear();
	return ans.second;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&p[i]);
		ans[i] = 1ll * p[i] * p[i];
	}
	for(int i=0; i<n-1; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
        lis.clear();
		for(auto &i : gph[x]){
			if(vis[i.second]) continue;
			que.push(i.second);
			dfs(i.second, x, i.first, x);
			lis.push_back(sub);
			for(auto &j : sub){
				ans[j.second] = min(ans[j.second], j.first + 1ll * p[x] * p[j.second]);
				ans[x] = min(ans[x], j.first + 1ll * p[x] * p[j.second]);
			}
			sub.clear();
		}
		cht.clear();
		for(auto &v : lis){
			for(auto &j : v){
				ans[j.second] = min(ans[j.second], cht.query(p[j.second]) + j.first);
			}
			for(auto &j : v){
				cht.add(p[j.second], j.first);
			}
		}
		reverse(lis.begin(), lis.end());
		cht.clear();
		for(auto &v : lis){
			for(auto &j : v){
				ans[j.second] = min(ans[j.second], cht.query(p[j.second]) + j.first);
			}
			for(auto &j : v){
				cht.add(p[j.second], j.first);
			}
		}
		vis[x] = 1;
	}
	lint dap = 0;
	for(int i=1; i<=n; i++) dap += ans[i];
	cout << dap;
}
