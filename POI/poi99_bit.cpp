#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, m;
char str[200][200];
int s[444][444];

int getsum(int x, int y, int d){
	int sx = x + y - d;
	int ex = x + y + d;
	int sy = x - y - d + 200;
	int ey = x - y + d + 200;
	sx = max(sx, 1);
	sy = max(sy, 1);
	ex = min(ex, 400);
	ey = min(ey, 400);
	return s[ex][ey] - s[sx-1][ey] - s[ex][sy-1] + s[sx-1][sy-1];
}

int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		cin >> (str[i] + 1);
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(str[i][j] == '1') s[i+j][i-j+200]++;
		}
	}
	for(int i=1; i<=400; i++){
		for(int j=1; j<=400; j++){
			s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			int s = 0, e = 400;
			while(s != e){
				int m = (s+e)/2;
				if(getsum(i, j, m)) e = m;
				else s = m+1;
			}
			printf("%d ", s);
		}
		puts("");
	}
}

