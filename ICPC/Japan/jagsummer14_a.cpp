#include <bits/stdc++.h>
#define sz(v)((int)(v).size())
#define all(v)(v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using point = complex<llf>;
using pi = pair<lint, lint>;
const int MAXN = 1000005;
const int mod = 1e9 + 7;

string s[MAXN];
vector<int> gph[MAXN];

void dfs(int x, int d){
	for(int j = 0; j < d; j++) putchar('.');
	puts(s[x].c_str());
	for(auto &y : gph[x]) dfs(y, d+1);
}

int main(){
	int n, m, t;
	cin >> n;
	for(int i = 0; i < n; i++){
		int p;
		cin >> p >> s[i+1];
		gph[p].push_back(i + 1);
	}
	dfs(1, 0);
}
