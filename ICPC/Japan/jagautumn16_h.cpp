#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10005;

int dp[MAXN];
int chk[MAXN];
int w, h, k, n;

int max_matching(vector<int> v, int w){
	for(auto &i : v) chk[i] = 1;
	for(int i=1; i<=(w+1)/2; i++){
		dp[i] = dp[i-1];
		if(i > 1 && !chk[2*i-2]) dp[i] = max(dp[i], dp[i-2] + 2);
		if(!chk[2*i-1]) dp[i] = max(dp[i], dp[i-1] + 1);
	}
	for(auto &i : v) chk[i] = 0;
	return dp[(w+1)/2];
}

vector<int> v[MAXN];

int main(){
	scanf("%d %d %d %d",&w,&h,&k,&n);
	k -= (w + 1) / 2;
	if(k < 0){
		puts("-1");
		return 0;
	}
	for(int i=0; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		if(y & 1) continue;
		v[y / 2].push_back(x);
	}
	int tot = 0;
	int D[3] = {};
	for(int i=1; i<=h/2; i++){
		int val = max_matching(v[i], w);
		D[1] += val;
		D[2] += (w + 1) / 2 - val;
	}
	for(int i=2; i; i--){
		int dx = min(D[i], k);
		D[i] -= dx;
		k -= dx;
	}
	cout << D[1] + 2 * D[2] << endl;
}
