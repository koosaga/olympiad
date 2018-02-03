#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, lint> pi;
const int MAXN = 2005;

string s;
lint k;
bool vis[MAXN][MAXN];
pi dp[MAXN][MAXN];

pi f(int x, int y){
	if(x > y) return pi(0, 1);
	if(x == y) return pi(1, 1);
	if(vis[x][y]) return dp[x][y];
	vis[x][y] = 1;
	if(s[x] == s[y]){
		pi tmp = f(x+1, y-1);
		tmp.first+=2;
		return dp[x][y] = tmp;
	}
	else{
		pi ret1 = f(x+1, y);
		pi ret2 = f(x, y-1);
		if(ret1 > ret2) swap(ret1, ret2);
		if(ret1.first == ret2.first) ret1.second += ret2.second;
		ret1.second = min(ret1.second, k + 100);
		ret1.first+=2;
		return dp[x][y] = ret1;
	}
}

string track(int x, int y, lint k){
	if(x > y) return "";
	if(x == y) return string(1, s[x]);
	if(s[x] == s[y]) return string(1, s[x]) + track(x+1, y-1, k) + string(1, s[y]);
	else{
		pi ret1 = f(x+1, y);
		pi ret2 = f(x, y-1);
		if(ret1.first < ret2.first) return string(1, s[x]) + track(x+1, y, k) + string(1, s[x]);
		if(ret1.first > ret2.first) return string(1, s[y]) + track(x, y-1, k) + string(1, s[y]);
		if(s[x] < s[y]){
			if(ret1.second < k) return string(1, s[y]) + track(x, y-1, k - ret1.second) + string(1, s[y]);
			else return string(1, s[x]) + track(x+1, y, k) + string(1, s[x]);
		}
		else{
			if(ret2.second < k) return string(1, s[x]) + track(x+1, y, k - ret2.second) + string(1, s[x]);
			else return string(1, s[y]) + track(x, y-1, k) + string(1, s[y]);
		}
	}
}

int main(){
	cin >> s >> k;
	if(f(0, s.size()-1).second < k) cout << "NONE\n";
	else cout << track(0, s.size() - 1, k) << "\n";
}
