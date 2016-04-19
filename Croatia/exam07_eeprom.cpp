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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int oo = 1e9;

int popcnt[1<<16];

int n;
char str[50][17];

int dp[2][17][1<<16][2];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> str[i];
	for(int i=0; i<(1<<16); i++) popcnt[i] = popcnt[i>>1] + (i&1);
	for(int x=n-1; x>=0; x--){
		for(int y=16; y>=0; y--){
			for(int z=0; z<(1<<16); z++){
				for(int b=0; b<2; b++){
					if(y == 16){
						if(x == n-1) dp[x&1][y][z][b] = popcnt[z] + b;
						else dp[x&1][y][z][b] = dp[(x+1)&1][0][z][0] + b;
						continue;
					}
					if((str[x][y] - '0') ^ ((z >> y) & 1) ^ b){
						dp[x&1][y][z][b] = min(dp[x&1][y+1][z^(1<<y)][b], dp[x&1][y+1][z][b^1]) + 1;
					}
					else{
						dp[x&1][y][z][b] = min(dp[x][y+1][z][b], dp[x][y+1][z^(1<<y)][b^1] + 2);
					}
				}
			}
		}
	}
	cout << dp[0][0][0][0]/2;
}