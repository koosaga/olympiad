#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using pi = pair<int, int>;

int n, m, k;
int s[MAXN], e[MAXN], x[MAXN];
int minv[2][MAXN];
vector<pi> v1[MAXN], v2[MAXN];

int main(){
	memset(minv, 0x3f, sizeof(minv));
	scanf("%d %d %d",&n,&m,&k);
	if(k > 5){
		puts("-1");
		return 0;
	}
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&s[i],&e[i],&x[i]);
		if(s[i] > e[i]) swap(s[i], e[i]);
	}
	while(k < 5){
		k++;
		s[m] = n, e[m] = n+1, x[m] = 0;
		n++;
		m++;
	}
	for(int i=0; i<m; i++){
		if(s[i] == 1 && e[i] < n){
			minv[0][e[i]] = min(minv[0][e[i]], x[i]);
		}
		if(s[i] > 1 && e[i] == n){
			minv[1][s[i]] = min(minv[1][s[i]], x[i]);
		}
	}
	for(int i=0; i<m; i++){
		if(minv[0][e[i]] < 5e8) v1[s[i]].push_back(pi(minv[0][e[i]] + x[i], e[i]));
		if(minv[0][s[i]] < 5e8) v1[e[i]].push_back(pi(minv[0][s[i]] + x[i], s[i]));
		if(minv[1][e[i]] < 5e8) v2[s[i]].push_back(pi(minv[1][e[i]] + x[i], e[i]));
		if(minv[1][s[i]] < 5e8) v2[e[i]].push_back(pi(minv[1][s[i]] + x[i], s[i]));
	}
	for(int i=2; i<n; i++){
		for(int j=0; j<v1[i].size() && j < 3; j++){
			swap(v1[i][j], *min_element(v1[i].begin() + j, v1[i].end()));
		}
		if(v1[i].size() > 3) v1[i].resize(3);
		for(int j=0; j<v2[i].size() && j < 3; j++){
			swap(v2[i][j], *min_element(v2[i].begin() + j, v2[i].end()));
		}
		if(v2[i].size() > 3) v2[i].resize(3);
	}
	int ans = 2e9;
	for(int i=0; i<m; i++){
		if(s[i] == 1 || e[i] == n) continue;
		for(auto &j : v1[s[i]]){
			if(j.second == e[i]) continue;
			for(auto &k : v2[e[i]]){
				if(k.second == s[i]) continue;
				if(j.second == k.second) continue;
				ans = min(ans, j.first + k.first + x[i]);
			}
		}
		for(auto &j : v2[s[i]]){
			if(j.second == e[i]) continue;
			for(auto &k : v1[e[i]]){
				if(k.second == s[i]) continue;
				if(j.second == k.second) continue;
				ans = min(ans, j.first + k.first + x[i]);
			}
		}
	}
	if(ans > 1e9) ans = -1;
	cout << ans << endl;
}
