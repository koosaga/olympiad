#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 105;
 
int k, p[MAXN], mark[MAXN];
int dep[MAXN];
vector<int> gph[MAXN];
vector<int> ans;
 
void dfs(int x){
	k--;
	for(auto &i : gph[x]){
		if(mark[i]) continue;
		if(k > 0){
			ans.push_back(i);
			dfs(i);
			ans.push_back(x);
		}
	}
}
 
int main(){
	int tc; scanf("%d",&tc);
	for(int i = 0; i < tc; i++){
		int n; scanf("%d %d",&n,&k);
		int pmax = 1;
		for(int j = 2; j <= n; j++){
			scanf("%d",&p[j]);
			gph[p[j]].push_back(j);
			dep[j] = dep[p[j]] + 1;
			if(dep[j] > dep[pmax]) pmax = j;
		}
		if(dep[pmax] + 1 >= k){
			vector<int> v;
			for(int j = pmax; j; j = p[j]) v.push_back(j);
			reverse(all(v));
			v.resize(k);
			printf("%d\n", sz(v) - 1);
			for(auto &i : v) printf("%d ", i);
		}
		else{
			k -= dep[pmax] + 1;
			vector<int> v;
			for(int j = pmax; j; j = p[j]){
				v.push_back(j);
				mark[j] = 1;
			}
			reverse(all(v));
			ans.clear();
			for(auto &i : v){
				ans.push_back(i);
				k++;
				dfs(i);
			}
			printf("%d\n", sz(ans) - 1);
			for(auto &i : ans) printf("%d ", i);
		}
		for(int i = 0; i < MAXN; i++){
			mark[i] = 0;
			gph[i].clear();
			p[i] = 0;
		}
		puts("");
	}
}
