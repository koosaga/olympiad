#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 200005;

int n;
int par[18][MAXN], dep[MAXN];
int din[MAXN], dout[MAXN], c[MAXN], piv;
lint dis[MAXN], ret[MAXN];
vector<pi> gph[MAXN];
vector<int> vc[MAXN];

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x <= n){
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
}bit;

void add_point(int x){
	bit.add(din[x], 1);
}

int query_sub(int x){
	if(x == 0) return 1e9;
	return bit.query(dout[x]) - bit.query(din[x] - 1);
}

void dfs(int x, int p){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		par[0][i.second] = x;
		dep[i.second] = dep[x] + 1;
		dfs(i.second, x);
	}
	dout[x] = piv;
}

void getC(){
	c[1] = 1;
	for(int i=2; i<=n; i++){
		add_point(i);
		int v = i;
		for(int j=17; j>=0; j--){
			if(query_sub(par[j][v]) < (i + 1) / 2){
				v = par[j][v];
			}
		}
		if(query_sub(v) < (i + 1) / 2) v = par[0][v];
		int w = c[i-1];
		for(int j=17; j>=0; j--){
			if(query_sub(par[j][w]) < (i + 1) / 2){
				w = par[j][w];
			}
		}
		if(query_sub(w) < (i + 1) / 2) w = par[0][w];
		if(dep[v] < dep[w]) c[i] = w;
		else c[i] = v;
	}
	for(int i=1; i<=n; i++) vc[c[i]].push_back(i);
}

vector<int> dfn;
bool proc[MAXN];
int sz[MAXN], msz[MAXN], col[MAXN];

void dfs2(int x, int p){
	dfn.push_back(x);
	sz[x] = 1;
	msz[x] = 0;
	for(auto &i : gph[x]){
		if(i.second == p || proc[i.second]) continue;
		dfs2(i.second, x);
		msz[x] = max(msz[x], sz[i.second]);
		sz[x] += sz[i.second];
	}
}

void dfs3(int x, int p, int c){
	dfn.push_back(x);
	col[x] = c;
	for(auto &i : gph[x]){
		if(i.second == p || proc[i.second]) continue;
		dis[i.second] = dis[x] + i.first;
		dfs3(i.second, x, c);
	}
}


int get_center(int x){
	dfn.clear();
	dfs2(x, -1);
	pi ans(1e9, x);
	for(auto &i : dfn){
		int k = max(sz[x] - sz[i], msz[i]);
		ans = min(ans, pi(k, i));
	}
	dfn.clear();
	return ans.second; 
}

lint cnt1[MAXN], cnt2[MAXN];

void dnc(){
	queue<int> que;
	que.push(1);
	while(!que.empty()){
		int x = que.front();
		que.pop();
		x = get_center(x);
		dfn.push_back(x);
		dis[x] = 0;
		for(auto &i : gph[x]){
			if(!proc[i.second]){
				dis[i.second] = i.first;
				dfs3(i.second, x, i.second);
			}
		}
		vector<int> aux;
		for(auto &i : dfn){
			for(auto &j : vc[i]){
				aux.push_back(j);
			}
		}
		sort(aux.begin(), aux.end());
		sort(dfn.begin(), dfn.end());
		for(auto &i : dfn) cnt1[i] = cnt2[i] = 0;
		int ptr = 0;
		lint sum = 0;
		for(auto &i : aux){
			while(ptr < dfn.size() && dfn[ptr] <= i){
				if(dfn[ptr] != x){
					int c = col[dfn[ptr]];
					cnt1[c]++;
					cnt2[c] += dis[dfn[ptr]];
				}
				sum += dis[dfn[ptr]];
				ptr++;
			}
			ret[i] += dis[c[i]] * ptr + sum;
			if(c[i] != x){
				ret[i] -= dis[c[i]] * cnt1[col[c[i]]];
				ret[i] -= cnt2[col[c[i]]];
			}
		}
		proc[x] = 1;
		for(auto &i : gph[x]){
			if(!proc[i.second]){
				que.push(i.second);
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=2; i<=n; i++){
		int x;
		scanf("%d %d",&par[0][i],&x);
		gph[par[0][i]].push_back(pi(x, i));
		gph[i].push_back(pi(x, par[0][i]));
	}
	dfs(1, 0);
	for(int i=1; i<18; i++){
		for(int j=1; j<=n; j++) par[i][j] = par[i-1][par[i-1][j]];
	}
	getC();
	dnc();
	for(int i=1; i<=n; i++) printf("%lld\n", ret[i]);
}
