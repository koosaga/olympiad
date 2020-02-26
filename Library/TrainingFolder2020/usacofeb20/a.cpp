#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int n, k;
vector<int> gph[MAXN];
bool good;

int dfs(int x, int p){
	vector<int> v;
	for(auto &i : gph[x]){
		if(i != p) v.push_back(dfs(i, x) + 1);
	}
	if(sz(v) % 2 == 0) v.push_back(0);
	sort(all(v));
	auto func = [&](int x){
		vector<int> w;
		if(sz(v) % 2 == 0) w.push_back(0);
		for(int j=0; j<sz(v); j++) if(j != x) w.push_back(v[j]);
		for(int i=0; i<sz(w)/2; i++){
			if(w[i] + w[sz(w)-1-i] < k) return 0;
		}
		return 1;
	};
	int s = 0, e = sz(v) - 1;
	if(!func(0)){
		good = 0;
		return v[0];
	}
	while(s != e){
		int m = (s+e+1)/2;
		if(func(m)) s = m;
		else e = m-1;
	}
	return v[s];
}

int rt;

bool trial(int x){
	k = x;
	good = 1;
	if(dfs(rt, -1) < k) good = 0;
	return good;
}

int main(){
	freopen("deleg.in", "r", stdin);
	freopen("deleg.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	if(n <= 3){
		cout << n-1 << endl;
		return 0;
	}
	rt = 1;
	while(sz(gph[rt]) > 1) rt++;
	int s = 1, e = n;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << s << endl;
}
