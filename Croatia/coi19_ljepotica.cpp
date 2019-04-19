#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 1e9 + 7;

int n, k, pwr[MAXN];
string s, t;
bool vis[MAXN][MAXN][2][2];
pi dp[MAXN][MAXN][2][2];

pi f(int x, int y, int matching, int mtch){
	if(y < 0) return pi(0, 0);
	if(x == n) return pi(0, y == 0);
	if(vis[x][y][matching][mtch]) return dp[x][y][matching][mtch];
	pi ret(0, 0);
	{
		int next_match = (s[x] == '0'); 
		int k_reduce = (matching != next_match);
		auto l = f(x + 1, y - k_reduce, next_match, mtch & (t[x] == '0'));
		ret.first += l.first;
		ret.second += l.second;
	}
	if(mtch == 0 || t[x] == '1'){
		int next_match = (s[x] == '1'); 
		int k_reduce = (matching != next_match);
		auto r = f(x + 1, y - k_reduce, next_match, mtch);
		ret.first += r.first + r.second * pwr[n - 1 - x];
		ret.second += r.second;
	}
	ret.first %= mod;
	ret.second %= mod;
	vis[x][y][matching][mtch] = 1;
	return dp[x][y][matching][mtch] = ret;
}

int solve(string x){
	memset(vis, 0, sizeof(vis));
	t = x;
	auto ans = f(1, k, 1, 1);
	auto ans2 = f(1, k, 0, 1);
	ans.first += ans2.first;
	ans.second += ans2.second;
	ans.first += ans.second * pwr[n - 1];
	return ans.first % mod;
}

int main(){
	pwr[0] = 1;
	for(int i=1; i<MAXN; i++){
		pwr[i] = (pwr[i-1] * 2) % mod;
	}
	cin >> n >> k >> s;
	s = "R" + s;
	for(auto &i : s){
		if(i == 'L') i = '0';
		else i = '1';
	}
	string l, r; cin >> l >> r;
	int ret = solve(r);
	l.back()--;
	for(int i=l.size() - 1; i>=0; i--){
		if(l[i] < '0'){
			l[i] += 2;
			l[i - 1] -= 1;
		}
		else break;
	}
	if(l.front() != '0'){
		ret += mod - solve(l);
	}
	cout << ret % mod << endl;
}
