#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 998244353;

string s;
int d;

map<vector<int>, int> mp;
int dfs(vector<int> v){
	if(*min_element(all(v)) > d) return 0;
	if(mp.find(v) != mp.end()) return mp[v];
	int ret = 0;
	if(v.back() == d) ret = 1;
	for(int i='A'; i<='Z'; i++){
		vector<int> w(sz(s) + 1);
		for(int j=0; j<=sz(s); j++){
			w[j] = v[j] + 1;
			if(j) w[j] = min(w[j], w[j-1] + 1);
			if(j) w[j] = min(w[j], v[j-1] + (i != s[j-1]));
		}
		ret += dfs(w);
		if(ret >= mod) ret -= mod;
	}
	return mp[v] = ret;
}

int main(){
	cin >> s >> d;
	vector<int> v(sz(s) + 1);
	iota(all(v), 0);
	cout << dfs(v) << endl;
}
