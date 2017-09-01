#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 500005;

vector<pi> gph[MAXN];
int n, m, vis[MAXN];
lint a[MAXN], b[MAXN], p[MAXN], sol;
vector<int> v;

void fuck(bool p){
	if(p){
		puts("NIE");
		exit(0);
	}
}

void dfs(int x){
	vis[x] = 1;
	v.push_back(x);
	for(auto &i : gph[x]){
		if(!vis[i.second]){
			a[i.second] = -a[x];
			b[i.second] = i.first - b[x];
			dfs(i.second);
		}
		else{
			if(a[i.second] == -a[x]){
				fuck(b[i.second] != i.first - b[x]);
			}
			else{
				lint k = i.first - b[x] - b[i.second];
				fuck(abs(k) % 2 != 0);
				k /= (2 * a[x]);
				if(sol == -1) sol = k;
				fuck(sol != k);
			}
		}
	}
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%lld",&p[i]);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		x = p[s] + p[e] - x;
		fuck(x < 0);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	lint ans1 = 0, ans2 = 0;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			v.clear();
			a[i] = 1;
			sol = -1;
			dfs(i);
			if(sol != -1){
				for(auto &j : v){
					lint w = sol * a[j] + b[j];
					fuck(w < 0 || w > p[j]);
					ans1 += w;
					ans2 += w;
				}
			}
			else{
				lint st = 0, ed = p[i];
				for(auto &j : v){
					if(a[j] == 1){
						st = max(st, 0 - b[j]);
						ed = min(ed, p[j] - b[j]);
					}
					else{
						st = max(st, b[j] - p[j]);
						ed = min(ed, b[j]);
					}
				}
				fuck(st > ed);
				lint c1 = 0, c2 = 0;
				for(auto &j : v){
					c1 += st * a[j] + b[j];
					c2 += ed * a[j] + b[j];
				}
				ans1 += min(c1, c2);
				ans2 += max(c1, c2);
			}
		}
	}
	printf("%lld %lld\n", ans1, ans2);
}
