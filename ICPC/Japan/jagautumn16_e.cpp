#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod1 = 1e9 + 409;
const int mod2 = 1e9 + 433;
const int MAXN = 200005;
int n;
lint H1[MAXN], H2[MAXN];
vector<int> gph[MAXN];

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i != p){
			dfs(i, x);
			H1[x] += H1[i] * 257;
			H2[x] += H2[i] * 257;
		}
	}
	H1[x]++;
	H2[x]++;
	H1[x] %= mod1;
	H2[x] %= mod2;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<n; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	dfs(1, 0);
	vector<pi> v;
	for(int i=1; i<=n; i++){
		v.emplace_back(H1[i], H2[i]);
	}
	lint ret = 0;
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[i] == v[e]) e++;
		ret += 1ll * (e - i - 1) * (e - i) / 2;
		i = e;
	}
	cout << ret << endl;
}
