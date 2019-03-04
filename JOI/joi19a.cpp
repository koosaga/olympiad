#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
using lint = long long;
 
int n, m;
char str[MAXN][MAXN];
int OS[MAXN][MAXN];
int IS[MAXN][MAXN];
 
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%s", str[i] + 1);
		for(int j=1; j<=m; j++){
			if(str[i][j] == 'O') OS[i][j]++;
			if(str[i][j] == 'I') IS[i][j]++;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			OS[i][j] += OS[i][j-1];
			IS[i][j] += IS[i-1][j];
		}
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(str[i][j] == 'J'){
				ret += (OS[i][m] - OS[i][j]) * (IS[n][j] - IS[i][j]);
			}
		}
	}
	cout << ret << endl;
}
 
