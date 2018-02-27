#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 1000005;

vector<int> gph[MAXN];
vector<int> ans;
int rem[MAXN], deg[MAXN];
int lbl[MAXN], ord[MAXN];
int n, m, k, cnt;

void dfs(int x, int l){
	if(l > k) return;
	if(x == cnt){
        if(ans.size() >= cnt - l) return;
		ans.clear();
		for(int i=0; i<cnt; i++){
			if(!rem[i]){
				ans.push_back(ord[i]);
			}
		}
		return;
	}
	if(rem[x]){
		dfs(x + 1, l + 1);
		return;
	}
	int increase_candidate = 0;
	for(auto &i : gph[x]){
		if(!rem[i]) increase_candidate++;
	}
	if(!increase_candidate){
		dfs(x + 1, l);
		return;
	}
	rem[x]++;
	dfs(x + 1, l + 1);
	rem[x]--;
	for(auto &i : gph[x]){
		rem[i]++;
	}
	dfs(x + 1, l);
	for(auto &i : gph[x]){
		rem[i]--;
	}
}

int s[MAXN * 3], e[MAXN * 3];

int main(){
	scanf("%d %d %d",&n,&k,&m);
	k = n - k;
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]);
		if(s[i] > e[i]) swap(s[i], e[i]);
		deg[s[i]]++;
		deg[e[i]]++;
	}
	int ecnt = 0;
	for(int i=1; i<=n; i++){
		if(deg[i] && deg[i] <= 2 * k){
			ord[cnt] = i;
			lbl[i] = cnt;
			cnt++;
		}
	}
	for(int i=0; i<m; i++){
		if(deg[s[i]] <= 2 * k && deg[e[i]] <= 2 * k){
			int ls = lbl[s[i]];
			int le = lbl[e[i]];
			if(ls > le) swap(ls, le);
			gph[ls].push_back(le);
			ecnt++;
		}
	}
	if(ecnt > 300){
		puts("NIE");
		return 0;
	}
	dfs(0, 0);
    for(int i=1; i<=n; i++) if(deg[i] == 0) ans.push_back(i);
	if((int)ans.size() < n - k){
		puts("NIE");
	}
	else{
		printf("%d\n", ans.size());
		sort(ans.begin(), ans.end());
		for(auto &i : ans) printf("%d ", i);
	}
}



