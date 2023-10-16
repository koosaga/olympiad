#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int n, k;

int main(){
	cin >> n >> k;
	vector<pi> v;
	if(n == 2){
		v.emplace_back(0, 0);
	} else if(n%2 == 1){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(i == j) continue;
				v.emplace_back(i, j);
			}
		}
	} else{
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(i == j) continue;
				if(i == n/2-1 && j == n/2) continue;
				if(j == n/2-1 && i == n/2) continue;
				v.emplace_back(i, j);
			}
		}
		v.emplace_back(n/2-1, n/2-1);
		v.emplace_back(n/2, n/2);
	}
	if(sz(v) < k) puts("NO");
	else{
		v.resize(k);
		vector<string> ans(n, string(n, '.'));
		for(auto &[x, y] : v) ans[x][y] = '#';
		puts("YES");
		for(auto &s : ans) puts(s.c_str());
	}
}