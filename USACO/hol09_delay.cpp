#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e8;

int n, d, k;
vector<int> zero, one;
bool vis[2005][2005];
int dp1[2005][2005], dp2[2005][2005]; // dp1 = mod, dp2 = exceed

void f(int x, int y){
	if(x == n){
		dp1[x][y] = dp2[x][y] = 1;
		return;
	}
	if(vis[x][y])return;
	vis[x][y] = 1;
	if(x-y < zero.size() && abs(zero[x-y] - x) <= d){
		f(x+1, y);
		dp1[x][y] += dp1[x+1][y];
		dp2[x][y] += dp2[x+1][y];
		dp1[x][y] %= mod;
		dp2[x][y] = min(dp2[x][y], mod+1);
	}
	if(y < one.size() && abs(one[y] - x) <= d){
		f(x+1, y+1);
		dp1[x][y] += dp1[x+1][y+1];
		dp2[x][y] += dp2[x+1][y+1];
		dp1[x][y] %= mod;
		dp2[x][y] = min(dp2[x][y], mod+1);
	}
}

string w;

void trk(int x, int y, int k){
	if(x == n) return;
	if(x-y < zero.size() && abs(zero[x-y] - x) <= d){
		if(dp2[x+1][y] >= k){
			w.push_back('0');
			trk(x+1, y, k);
			return;
		}
		else k -= dp2[x+1][y];
	}
	w.push_back('1');
	trk(x+1, y+1, k);
}

int main(){
	cin >> n >> d >> k;
	string s;
	cin >> s;
	for(int i=0; i<n; i++){
		if(s[i] == '0') zero.push_back(i);
		else one.push_back(i);
	}
	f(0, 0);
	cout << dp1[0][0] << endl;
	trk(0, 0, k);
	cout << w;
}
