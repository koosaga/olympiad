#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 500005;

struct disj{
    int pa[MAXN];
    void init(int n){
        for(int i=0; i<=n; i++) pa[i] = i;
    }
    int find(int x){
        return pa[x] = (pa[x] == x ? x : find(pa[x]));
    }
    bool uni(int p, int q){
        p = find(p);
        q = find(q);
        if(p == q) return 0;
        pa[q] = p;
        return 1;
    }
}disj;
 
int n, m;
int out[MAXN];
 
vector<pi> graph[MAXN];
int vis[MAXN];
int par[MAXN];
 
int dfs(int x){
    int ret = par[x];
    vis[x] = 1;
    for(int i=0; i<graph[x].size(); i++){
        if(vis[graph[x][i].second]) continue;
        if(dfs(graph[x][i].second)){
            ret++;
            out[graph[x][i].first] = 1;
        }
    }
    return ret % 2;
}
 
bool mian(int n, vector<pi> v){
	int m = sz(v);
	vector<int> s(m), e(m);
    disj.init(n);
    for(int i=0; i<m; i++){
    	s[i] = v[i].first;
    	e[i] = v[i].second;
        if(!disj.uni(s[i], e[i])) continue;
        else{
            graph[s[i]].push_back(pi(i, e[i]));
            graph[e[i]].push_back(pi(i, s[i]));
        }
    }
    for(int i=1; i<=n; i++){
        if(!vis[i] && dfs(i)){
            return 0;
        }
    }
    return 1;
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		int n, m; scanf("%d %d",&n,&m);
		vector<int> ans(m);
		vector<pi> v;
		for(int i=0; i<m; i++){
			int s, e, x;
			scanf("%d %d %d",&s,&e,&x);
			if(x == 0){
				v.emplace_back(s, e);
				ans[i] = -sz(v);
			}
			else{
				par[s] ^= 1;
				par[e] ^= 1;
				ans[i] = 1;
			}
		}
		if(!mian(n, v)) puts("NIE");
		else{
			puts("TAK");
			for(int i=0; i<m; i++){
				if(ans[i] < 0) printf("%d\n", out[-1-ans[i]]);
				else puts("1");
			}
		}
		memset(par, 0, sizeof(int) * (n+2));
		memset(vis, 0, sizeof(int) * (n+2));
		for(int i=0; i<=n+2; i++) graph[i].clear();
		memset(out, 0, sizeof(int) * (m+2));
	}
}
