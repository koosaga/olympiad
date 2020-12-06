#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 500005;

vector<pi> gph[MAXN];
int n, m, vis[MAXN];
lint a[MAXN], b[MAXN], sol;
vector<int> v;
lint dap[MAXN];

void fuck(bool p){
	if(p){
		puts("NO");
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
				if(sol == -69696969) sol = k;
				fuck(sol != k);
			}
		}
	}
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		x *= 2;
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	lint ans1 = 0, ans2 = 0;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			v.clear();
			a[i] = 1;
			sol = -69696969;
			dfs(i);
			if(sol != -69696969){
				for(auto &j : v){
					dap[j] = sol * a[j] + b[j];
				}
			}
			else{
				vector<int> med;
				lint st = 0; 
				for(auto &j : v){
					if(a[j] == 1) med.push_back(-b[j]);
					else med.push_back(b[j]);
				}
				sort(all(med));
				st = med[sz(med) / 2];
				for(auto &j : v){
					dap[j] = st * a[j] + b[j];
				}
			}
		}
	}
	puts("YES");
	for(int i=1; i<=n; i++) printf("%.1f ", 0.5 * dap[i]);
}

