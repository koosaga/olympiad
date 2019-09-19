#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
using lint = long long;
#define sz(v) ((int)(v).size())


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
	int kth(int x){
		int pos = 0;
		for(int i=17; i>=0; i--){
			if((pos|(1<<i)) < MAXN && tree[pos+(1<<i)] < x){
				pos += (1<<i);
				x -= tree[pos];
			}
		}
		return pos + 1;
	}
}bit;

int n;
vector<int> gph[MAXN];
int par[18][MAXN], dep[MAXN];
int din[MAXN], dout[MAXN], rev[MAXN], piv;

namespace CD{
	vector<int> dfn;
	int sz[MAXN], msz[MAXN], vis[MAXN];
	int dep[MAXN];
	int dist[18][MAXN];
	vector<lint> idx_sum[MAXN], idx_cnt[MAXN];
	lint dist_sum[MAXN];
	lint dist_cnt[MAXN];
	pi par[MAXN]; // (which node, which index)
	void dfs(int x, int p){
		sz[x] = 1; msz[x] = 0;
		dfn.push_back(x);
		for(auto &i : gph[x]){
			if(i != p && !vis[i]){
				dfs(i, x);
				sz[x] += sz[i];
				msz[x] = max(msz[x], sz[i]);
			}
		}
	}
	int get_center(int x){
		dfn.clear();
		dfs(x, -1);
		pi ret(1e9, -1);
		for(auto &i : dfn){
			ret = min(ret, pi(max(sz(dfn) - sz[i], msz[i]), i));
		}
		return ret.second;
	}
	void fill_table(int x, int p, int e){
		for(auto &i : gph[x]){
			if(i != p && !vis[i]){
				dist[e][i] = dist[e][x] + 1;
				fill_table(i, x, e);
			}
		}
	}
	void init(){
		queue<int> que;
		que.push(1);
		while(!que.empty()){
			int x = que.front(); que.pop();
			pi bk = par[x];
			int bl = dep[x];
			x = get_center(x);
			par[x] = bk;
			dep[x] = bl;
			vis[x] = 1;
			fill_table(x, -1, dep[x]);
			for(auto &i : gph[x]){
				if(!vis[i]){
					idx_sum[x].push_back(0);
					idx_cnt[x].push_back(0);
					par[i] = pi(x, sz(idx_sum[x]) - 1);
					dep[i] = dep[x] + 1;
					que.push(i);
				}
			}
		}
	}
	void add(int x, int v){
		int pae = -1;
		for(int i=x; i; i=par[i].first){
			int curDist = dist[dep[i]][x];
			dist_sum[i] += v * curDist;
			dist_cnt[i] += v;
			if(pae != -1){
				idx_sum[i][pae] += v * curDist;
				idx_cnt[i][pae] += v;
			}
			pae = par[i].second;
		}
	}
	lint query(int x){
		lint ret = 0;
		int pae = -1;
		for(int i=x; i; i=par[i].first){
			ret += dist_sum[i] + 1ll * dist[dep[i]][x] * dist_cnt[i];
			if(pae != -1) ret -= idx_sum[i][pae] + idx_cnt[i][pae] * dist[dep[i]][x];
			pae = par[i].second;
		}
		return ret;
	}
}

void dfs(int x, int p){
	din[x] = ++piv;
	rev[din[x]] = x;
	for(auto &i : gph[x]){
		if(i != p){
			par[0][i] = x;
			dep[i] = dep[x] + 1;
			dfs(i, x);
		}
	}
	dout[x] = piv;
}

int cnt[MAXN], alive;

lint getdist(int x, int p, int d){
	lint ret = 1ll * d * cnt[x];
	for(auto &i : gph[x]){
		if(i != p){
			ret += getdist(i, x, d + 1);
		}
	}
	return ret;
}

int get_cen(int x){
	auto in_par = [&](int x){
		return alive - 
		(bit.query(dout[x]) - bit.query(din[x] - 1));
	};
	for(int i=17; i>=0; i--){
		if(par[i][x] && in_par(par[i][x]) > alive / 2){
			x = par[i][x];
		}
	}
	if(par[0][x] && in_par(x) > alive / 2) x = par[0][x];
	return x;
}

char buf[5];
int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		gph[x].push_back(y);
		gph[y].push_back(x);
	}
	dfs(1, 0);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++){
			par[i][j] = par[i-1][par[i-1][j]];
		}
	}
	CD::init();
	int q; scanf("%d",&q);
	while(q--){
		int x;
		scanf("%s %d",buf,&x);
		if(*buf == '+'){
			cnt[x]++;
			bit.add(din[x], +1);
			CD::add(x, +1);
			alive++;
		}
		else{
			cnt[x]--;
			bit.add(din[x], -1);
			CD::add(x, -1);
			alive--;
		}
		if(alive == 0) puts("0");
		else{
			int w = get_cen(rev[bit.kth(alive / 2 + 1)]);
			printf("%lld\n", CD::query(w));
		}
	}
}
