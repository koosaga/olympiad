#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using pi = pair<int, int>;

int n;
char s[MAXN], t[MAXN];
int dp[MAXN][5];

int getCost(int x, int p){
	char c = x + '0';
	if(c == '2') c = s[p];
	return c != t[p];
}

int moveCost(int p1, int p2, int x1, int x2){ 
	x1 /= 2, x2 /= 2;
	int arg1 = getCost(x1, p1) != getCost(x2, p2);
	int arg2 = x1 != x2;
	return arg1 + arg2;
}

int adj[5][5] = {
	{1, 0, 1, 0, 1},
	{0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1},
	{0, 1, 0, 1, 1},
	{1, 0, 0, 1, 1}};

int main(){
	scanf("%d %s %s",&n,s+1,t+1);
	fill(dp[0], dp[0] + 4, 1e9);
	t[0] = '0'; t[n+1] = '0';
	s[0] = '0', s[n+1] = '0';
	for(int i=1; i<=n+1; i++){
		for(int j=0; j<5; j++){
			dp[i][j] = 1e9;
			for(int k=0; k<5; k++){
				if(!adj[k][j]) continue;
				dp[i][j] = min(dp[i][j], dp[i-1][k] + moveCost(i-1, i, k, j) + (j == 4 && (k == 1 || k == 2)));
			}

		}
	}
	cout << dp[n+1][4] / 2<< endl;
}
