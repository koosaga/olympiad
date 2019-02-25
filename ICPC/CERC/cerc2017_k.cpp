#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 505;

int n, a[MAXN];
int p[3], c[7], v[3];

short dp[MAXN][MAXN][MAXN];

short f(int x, int y, int z){
	if(x + y + z == 0) return 0;
	if(~dp[x][y][z]) return dp[x][y][z];
	short ans = -1e4;
	for(int i=0; i<=7 && i <= x; i++){
		for(int j=0; i+j<=7 && j <= y; j++){
			for(int k=0; i+j+k<=7 && k <= z; k++){
				if(i + j + k == 0) continue;
				if((i * p[0] + j * p[1] + k * p[2]) % 7 == 0){
					ans = max(ans, (short)(f(x-i, y-j, z-k) + 1));
				}
			}
		}
	}
	return dp[x][y][z] = ans;
}

int solve(){
	if(c[1]) p[0] = 1;
	else p[0] = 6;
	if(c[2]) p[1] = 2;
	else p[1] = 5;
	if(c[3]) p[2] = 3;
	else p[2] = 4;
	v[0] = max(c[1], c[6]);
	v[1] = max(c[2], c[5]);
	v[2] = max(c[3], c[4]);
	memset(dp, -1, sizeof(dp));
	return f(v[0], v[1], v[2]);
}

int main(){
	cin >> n;
	vector<int> v = {0};
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		bool ok = true;
		for(int j=1; j<7; j++){
			if(s[j-1] != s[j]) ok = false;
		}
		if(ok == false){
			string mx = s;
			int mxp = 0;
			for(int j=1; j<7; j++){
				rotate(s.begin(), s.begin() + 1, s.end());
				if(mx < s){
					mx = s;
					mxp = j;
				}
			}
			v.push_back(mxp);
		}
	}
	v.push_back(0);
	n  = v.size() - 2;
	for(int i=0; i+1<v.size(); i++){
		c[(v[i+1] - v[i] + 7) % 7]++;
	}
	int ans = c[0];
	c[0] = 0;
	int x = min(c[1], c[6]);
	ans += x, c[1] -= x, c[6] -= x;
	x = min(c[2], c[5]);
	ans += x, c[2] -= x, c[5] -= x;
	x = min(c[3], c[4]);
	ans += x, c[3] -= x, c[4] -= x;
	ans += solve();
	cout << n + 1 - ans << endl;
}

