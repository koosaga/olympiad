#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 305;
const int mod = 100000;
using pi = pair<int, int>;
#define sz(v) int((v).size())

int n;
int adj[15][15];
int dp[1<<15], tra[1<<15];
int good[1<<15];
int ord[15];

string s[100], t[100];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		cin >> s[i] >> t[i];
		int x = s[i][0] - 'L';
		int y = t[i][0] - 'L';
		adj[x][y] = adj[y][x] = 1;
	}
	for(int i=0; i<(1<<15); i++){
		good[i] = 1;
		for(int j=0; j<15; j++){
			for(int k=0; k<15; k++){
				if((i >> j) % 2 == 1 && (i >> k) % 2 == 1 && adj[j][k]){
					good[i] = 0;
					break;
				}
			}
		}
	}
	for(int i=1; i<(1<<15); i++){
		dp[i] = 1e9;
		for(int j=i; j; j=(j-1)&i){
			if(good[j]){
				if(dp[i] > dp[i^j] + 1){
					dp[i] = dp[i^j] + 1;
					tra[i] = j;
				}
			}
		}
	}
	cout << dp[(1<<15) - 1] - 2 << endl;
	int cnt = 1;
	for(int j=(1<<15)-1; j; ){
		int t = tra[j];
		j ^= t;
		for(int k=0; k<15; k++){
			if((t >> k) & 1) ord[k] = cnt;
		}
		cnt++;
	}
	for(int i=0; i<n; i++){
		int x = s[i][0] - 'L';
		int y = t[i][0] - 'L';
		assert(ord[x] != ord[y]);
		if(ord[x] < ord[y]) swap(s[i], t[i]);
		cout << s[i] << " " << t[i] << endl;
	}
}
