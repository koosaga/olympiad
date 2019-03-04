#include <bits/stdc++.h>
using namespace std;
const int MAXN = 405;
using lint = long long;
using pi = pair<int, int>;
 
int n;
char str[MAXN];
int dp[222][222][222][4];
vector<int> rep[3];
int sum[3][MAXN];
 
int cntAfter(char arg, int pos){
	if(arg == 'R') return sum[0][pos + 1];
	if(arg == 'G') return sum[1][pos + 1];
	if(arg == 'Y') return sum[2][pos + 1];
	assert(0);
}
 
int cost(int cR, int cG, int cY, int mode){
	int pos = -1;
	if(mode == 0) pos = rep[mode][cR-1];
	if(mode == 1) pos = rep[mode][cG-1];
	if(mode == 2) pos = rep[mode][cY-1];
	return
	max(cntAfter('R', pos) - cR, 0) +
	max(cntAfter('G', pos) - cG, 0) +
	max(cntAfter('Y', pos) - cY, 0);
}
 
int f(int cR, int cG, int cY, int prv){
	if(cR + cG + cY == 0) return 0;
	if(~dp[cR][cG][cY][prv]) return dp[cR][cG][cY][prv];
	int ret = 1e9;
	if(cR > 0 && prv != 0){
		ret = min(ret, f(cR - 1, cG, cY, 0) + cost(cR, cG, cY, 0));
	}
	if(cG > 0 && prv != 1){
		ret = min(ret, f(cR, cG - 1, cY, 1) + cost(cR, cG, cY, 1));
	}
	if(cY > 0 && prv != 2){
		ret = min(ret, f(cR, cG, cY - 1, 2) + cost(cR, cG, cY, 2));
	}
	return dp[cR][cG][cY][prv] = ret;
}
 
int main(){
	cin >> n >> str;
	memset(dp, -1, sizeof(dp));
	int cntr = count(str, str + n, 'R');
	int cntg = count(str, str + n, 'G');
	int cnty = count(str, str + n, 'Y');
	if(max({cntr, cntg, cnty}) > 202){
		puts("-1");
		return 0;
	}
	for(int i=n-1; i>=0; i--){
		if(str[i] == 'R'){
			rep[0].push_back(i);
			sum[0][i]++;
		}
		if(str[i] == 'G'){
			rep[1].push_back(i);
			sum[1][i]++;
		}
		if(str[i] == 'Y'){
			rep[2].push_back(i);
			sum[2][i]++;
		}
		for(int j=0; j<3; j++) sum[j][i] += sum[j][i+1];
	}
	int ans = f(cntr, cntg, cnty, 3);
	if(ans > 1e8) ans = -1;
	cout << ans << endl;
}
