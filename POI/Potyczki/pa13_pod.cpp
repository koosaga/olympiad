#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;
const int MAXL = 19;

int n;

namespace CD{
	struct node{
		int sub, dis, vtx;
		bool operator<(const node &n)const{
			return pi(dis, vtx) < pi(n.dis, n.vtx);
		}
	};
	struct foo{
		int par, vtx, sub;
	};
	vector<int> gph[MAXN];
	vector<int> dfn;
	int par[MAXN], pae[MAXN], dep[MAXN], vis[MAXN];
	int sz[MAXN], msz[MAXN];
	void add_edge(int s, int e){
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	void dfs(int x, int p){
		sz[x] = 1; msz[x] = 0;
		for(auto &i : gph[x]){
			if(i != p && !vis[i]){
				dfs(i, x);
				sz[x] += sz[i];
				msz[x] = max(msz[x], sz[i]);
			}
		}
		dfn.push_back(x);
	}
	int get_center(int x){
		dfn.clear();
		dfs(x, -1);
		pi ret(1e9, -1);
		for(auto &i : dfn){
			int val = max(msz[i], sz(dfn) - sz[i]);
			ret = min(ret, pi(val, i));
		}
		return ret.second;
	}
	int dist[MAXL][MAXN];
	int sub[MAXL][MAXN];
	vector<node> vect[MAXN];
	int ptr[MAXN];
	void init(){
		queue<int> que;
		que.push(1);
		while(sz(que)){
			int px = que.front(); que.pop();
			int x = get_center(px);
			tie(par[x], pae[x], dep[x]) = make_tuple(par[px], pae[px], dep[px]);
			vis[x] = 1;
			{
				vect[x].push_back({-1, 0, x});
				sub[dep[x]][x] = -1;
				queue<foo> que;
				for(auto &i : gph[x]){
					if(!vis[i]){
						que.push({x, i, i});
						dist[dep[x]][i] = 1;
					}
				}
				while(sz(que)){
					auto fr = que.front(); que.pop();
					vect[x].push_back({fr.sub, dist[dep[x]][fr.vtx], fr.vtx});
					for(auto &i : gph[fr.vtx]){
						if(!vis[i] && i != fr.par){
							que.push({fr.vtx, i, fr.sub});
							dist[dep[x]][i] = dist[dep[x]][fr.vtx] + 1;
							sub[dep[x]][i] = sub[dep[x]][fr.vtx];
						}
					}
				}
			}
			sort(all(vect[x]));
			ptr[x] = sz(vect[x]);
			for(auto &i : gph[x]){
				if(!vis[i]){
					par[i] = x;
					pae[i] = i;
					dep[i] = dep[x] + 1;
					que.push(i);
				}
			}
		}
		memset(vis, 0, sizeof(vis));
	}
	int query(int x){
		pi ret(-1, -1);
		int base_sub = -1;
		for(int i=x; i; i=par[i]){
			int base_dist = dist[dep[i]][x];
			while(sz(vect[i]) && vis[vect[i].back().vtx]){
				vect[i].pop_back();
			}
			ptr[i] = min(ptr[i], sz(vect[i]));
			while(ptr[i] > 0 && (vect[i][ptr[i] - 1].sub == vect[i].back().sub ||
				vis[vect[i][ptr[i] - 1].vtx])){
				ptr[i]--;
			}
			if(sz(vect[i]) && base_sub != vect[i].back().sub){
				ret = max(ret, pi(base_dist + vect[i].back().dis, vect[i].back().vtx));
			}
			if(ptr[i] && base_sub != vect[i][ptr[i] - 1].sub){
				ret = max(ret, pi(base_dist + vect[i][ptr[i] - 1].dis, vect[i][ptr[i] - 1].vtx));
			}
			base_sub = pae[i];
		}
		return ret.second;
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e; scanf("%d %d",&s,&e);
		CD::add_edge(s, e);
	}
	CD::init();
	printf("1");
	int pos = 1;
	for(int i=0; i<n-1; i++){
		CD::vis[pos] = 1;
		pos = CD::query(pos);
		printf(" %d", pos);
	}
	puts("");
}
