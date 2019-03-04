#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 205;

char dp[MAXN][MAXN];
string x, t;

bool dfs(int s, int e){
	if(s == e) return true;
	if(~dp[s][e]) return dp[s][e];
	int p = (e - s) % t.size();
	p = (t.size() - p) % t.size();
	if(t[p] == x[s] && dfs(s+1, e)) return dp[s][e] = 1;
	for(int j=s+t.size(); j<e; j+=t.size()){
		if(dfs(s, j) && dfs(j, e)) return dp[s][e] = 1;
	}
	return dp[s][e] = 0;
}

int main(){
	string s;
	cin >> s;
	for(int i=1; i<s.size(); i++){
		if(s.size() % i) continue;
		string ans;
		ans.push_back('z' + 1);
		for(int j=0; j+i<=s.size(); j++){
			t = s.substr(j, i);
			x = s.substr(0, j) + s.substr(j + i, s.size() - j - i);
			memset(dp, -1, sizeof(dp));
			if(dfs(0, x.size())) ans = min(ans, t);
		}
		if(ans.front() != 'z' + 1){
			cout <<ans <<endl;
			return 0;
		}
	}
	cout <<s <<endl;
}

