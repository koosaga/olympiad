#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;

vector<pi> gph[MAXN];
int n, m, vis[MAXN];
lint a[MAXN], b[MAXN], sol;
bool hasSolution;

void my_assert(bool p){
	if(p){
		puts("No");
		exit(0);
	}
}

void dfs(int x){
	vis[x] = 1;
	for(auto &i : gph[x]){
		if(!vis[i.second]){
			a[i.second] = -a[x];
			b[i.second] = i.first - b[x];
			dfs(i.second);
		}
		else{
			if(a[i.second] == -a[x]){
				my_assert(b[i.second] != i.first - b[x]);
			}
			else{
				lint k = i.first - b[x] - b[i.second];
				my_assert(abs(k) % 2 != 0);
				k /= (2 * a[x]);
				if(!hasSolution){
					hasSolution = 1;
					sol = k;
				}
				my_assert(sol != k);
			}
		}
	}
}
int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].push_back(pi(x, e));
		gph[e].push_back(pi(x, s));
	}
	a[1] = 1;
	dfs(1);
	if(!hasSolution){
		vector<lint> v;
		for(int i = 1; i <= n; i++){
			v.push_back(-a[i] * b[i]);
		}
		sort(all(v));
		sol = v[sz(v) / 2];
	}
	puts("Yes");
	for(int i = 1; i <= n; i++) printf("%lld ", sol * a[i] + b[i]);
	return 0;
}

