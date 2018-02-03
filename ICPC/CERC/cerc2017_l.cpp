#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5300;
const int offset = 2600;

int a[MAXN][MAXN], b[MAXN][MAXN];
char buf[5];

bool query(int x, int y){
	x += offset;
	y -= offset;
	if(x < 0 || y < 0 || x >= MAXN || y >= MAXN) return false;
	if(b[x][y]) return true;
	return false;
}

int main(){
	int n, ans = 0;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y, d;
		scanf("%s %d %d %d",buf,&x,&y,&d);
		if(*buf == 'A'){
			int sx = x - d / 2 + offset;
			int ex = x + d / 2 + offset;
			int sy = y - d / 2 + offset;
			int ey = y + d / 2 + offset;
			a[sx][sy]++;
			a[ex][sy]--;
			a[sx][ey]--;
			a[ex][ey]++;
		}
		else{
			int sx = x - y - d/2 + offset;
			int ex = x - y + d/2 + offset;
			int sy = x + y - d/2 + offset;
			int ey = x + y + d/2 + offset;
			b[sx][sy]++;
			b[ex][sy]--;
			b[sx][ey]--;
			b[ex][ey]++;
		}
	}
	for(int i=1; i<MAXN; i++){
		for(int j=1; j<MAXN; j++){
			a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
			b[i][j] += b[i-1][j] + b[i][j-1] - b[i-1][j-1];
		}
	}
	for(int i=0; i<MAXN; i++){
		for(int j=0; j<MAXN; j++){
			if(a[i][j]) ans += 4;
			else{
				if(query(i-j-1, i+j)) ans++;
				if(query(i-j, i+j)) ans++;
				if(query(i-j-1, i+j+1)) ans++;
				if(query(i-j, i+j+1)) ans++;
			}
		}
	}
	printf("%.2f\n", ans * 0.25);
}
