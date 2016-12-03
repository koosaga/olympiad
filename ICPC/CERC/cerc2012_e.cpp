#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int t;
int n;

map<string, int> mp;
string p1[505];
string p2[505], p3[505];

int nxt1[505], nxt2[505];
bool mode[505];
string obj;

int dp[505][2005];

int f(int x, int y){
	if(~dp[x][y]) return dp[x][y];
	if(mode[x] == 1){
		int ret = y;
		for(auto &j : p1[x]){
			if(ret < obj.size() && obj[ret] == j) ret++;
		}
		return dp[x][y] = ret;
	}
	else{
		return dp[x][y] = f(nxt2[x], f(nxt1[x], y));
	}
}

int main(){
	cin >> t;
	while(t--){
		mp.clear();
		memset(dp, -1, sizeof(dp));
		int p = 0;
		cin >> n;
		for(int i=1; i<=n; i++){
			string x, y, z, w;
			cin >> x >> y >> z;
			mp[x] = i;
			if(z.front() <= 'z' && z.front() >= 'a'){
				p1[i] = z;
				mode[i] = 1;
			}
			else{
				mode[i] = 0;
				cin >> y >> w;
				p2[i] = z, p3[i] = w;
			}
		}
		for(int i=1; i<=n; i++){
			nxt1[i] = mp[p2[i]];
			nxt2[i] = mp[p3[i]];
		}
		string x;
		cin >> x >> obj;
		puts(f(mp[x], 0) == obj.size() ? "YES" : "NO");
	}
}