#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;
using pi = pair<int, int>;
using lint = long long;

int n, m;
int a[MAXN];
lint dp[20][MAXN][MAXN];

lint f(int k, int x, int y){
	if(k == 0) return 1;
	if(~dp[k][x][y]) return dp[k][x][y];
	lint ret = 0;
	for(int z = y+1; z < n; z++){
		if(a[x] + a[y] >= a[z]) ret += f(k-1, y, z);
	}
	return dp[k][x][y] = ret;
}

int main(){
	cin >> n >> m;
	for(int i = 0; i < n; i++) cin >> a[i];
	sort(a, a + n);
	memset(dp, -1, sizeof(dp));
	lint ret = 0;
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			for(int k = j+1; k < n; k++){
				if(a[i] + a[j] >= a[k]) ret += f(m - 3, j, k);
			}
		}
	}
	cout << ret << endl;
}

