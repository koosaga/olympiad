#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<int> gph[300005];
int chk[300005], cnt, lim;
int n, m;

int dfs(int x, int p){
	vector<int> v;
	for(auto &i : gph[x]){
		if(i == p) continue;
		int w = dfs(i, x);
		if(w != -1) v.push_back(w + 1);
	}
	sort(v.begin(), v.end());
	while(v.size() >= 2 && v.back() + v[v.size() - 2] > 2 * lim){
		v.pop_back();
		cnt++;
	}
	while(v.size() && v.back() > 2 * lim) v.pop_back(), cnt++;
	if(v.empty()) return chk[x] ? 0 : -1;
	return v.back();
}


int trial(int l){
	cnt = 1;
	lim = l;
	for(int i=1; i<=n; i++){
		if(chk[i]){
			dfs(i, -1);
			break;
		}
	}
	return cnt;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d",&chk[i]);
	if(*max_element(chk, chk + n + 1) == 0){
		puts("0");
		return 0;
	}
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int s = 0, e = n;
	while(s != e){
		int mi = (s+e)/2;
		if(trial(mi) <= m) e = mi;
		else s = mi+1;
	}
	cout << s;
}
