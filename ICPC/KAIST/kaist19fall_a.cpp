#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 505;
using lint = long long;
using pi = pair<int, int>;

int n, m;
char str[MAXN][MAXN];

int type(char c){
	if(c == '7') return 1;
	if(c == '8') return 0;
	return 2;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
	}
	int dap = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(type(str[i][j]) != type(str[n-1-i][m-1-j])){
				puts("-1");
				return 0;
			}
			if(type(str[i][j]) == 0) continue;
			if(pi(i, j) == pi(n-1-i, m-1-j)){
				puts("-1");
				return 0;
			}
			if(type(str[i][j]) == 1) dap++;
			if(type(str[i][j]) == 2 && str[i][j] == str[n-1-i][m-1-j]) dap++;
		}
	}
	cout << dap / 2 << endl;
}
