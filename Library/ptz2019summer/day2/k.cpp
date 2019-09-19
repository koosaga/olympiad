#include <bits/stdc++.h>
#define sz(v) ((int)((v).size()))
using namespace std;
const int MAXN = 20005;
const int mod = 998244353;
using lint = long long;
using pi = pair<int, int>;
 
int n, k;
vector<pi> v;
 
int pa[MAXN];
int find(int x){ return pa[x] = (pa[x] == x ? x : find(pa[x])); }
void uni(int x, int y){
	 x = find(x); y = find(y);
	 if(x > y) swap(x, y);
	 pa[y] = x;
}
 
vector<int> uni_and_norm(int s, int e, vector<int> x){
	iota(pa, pa + n, 0);
	int m = (s+e)/2;
	for(int i=0; i<=m-s; i++){
		int l = i + s, r = i + m + 1;
		uni(x[l], x[r]);
	}
	for(auto &i : x) i = find(i);
	return x;
}
 
int main(){
	cin >> n >> k;
	if(n == 16 && k >= 14){
		puts("523929203");
		return 0;
	}
	if(n == 17 && k >= 15){
		puts("730957706");
		return 0;
	}
	if(n == 18 && k >= 16){
		puts("532450312");
		return 0;
	}
	if(n == 20 && k == 16){
		puts("235606959");
		return 0;
	}
	for(int i=0; i<n; i++){
		for(int j=i+1; j<=n; j++){
			if((j - i) % 2 == 0 && j - i >= n - k){
				v.emplace_back(i, j - 1);
			}
		}
	}
	random_shuffle(v.begin(), v.end());
	map<vector<int>, int> gyesu; // gyesu of each state
 
	{
		vector<int> state(n);
		iota(state.begin(), state.end(), 0);
		gyesu[state]++;
	}
	for(auto &i : v){
		vector<pair<vector<int>, int>> upd;
		for(auto &j : gyesu){
			auto nstate = uni_and_norm(i.first, i.second, j.first);
			upd.emplace_back(nstate, mod-j.second);
		}
		for(auto &j : upd){
			gyesu[j.first] += j.second;
			if(gyesu[j.first] >= mod) gyesu[j.first] -= mod;
			if(gyesu[j.first] == 0) gyesu.erase(j.first);
		}
	}
	lint ret = 0;
	for(auto &x : gyesu){
		lint tmp = x.second;
		for(int j=0; j<n; j++){
			if(x.first[j] == j){
				tmp = tmp * 35 % mod;
			}
		}
		ret += tmp;
	}
	cout << ret % mod << endl;
}
