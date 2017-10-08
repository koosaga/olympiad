#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

const int offset = 1000;

int dx[2005][2005];
int a, b, n, q;
int cases;

int get(int sx, int ex, int sy, int ey){
	sx = max(sx,1);
	sy = max(sy,1);
	ex = min(ex,2*offset);
	ey = min(ey,2*offset);
	return dx[ex][ey] - dx[sx-1][ey] - dx[ex][sy-1] + dx[sx-1][sy-1];
}
bool solve(){
	cases++;
	scanf("%d %d %d %d",&a,&b,&n,&q);
	if(a == 0 && b ==0) return 0;
	printf("Case %d:\n",cases);
	memset(dx,0,sizeof(dx));
	for(int i=0; i<n; i++){
		int a, b;
		scanf("%d %d",&a,&b);
		dx[a + b][a - b + offset]++;
	}
	for(int i=0; i<=2*offset; i++){
		for(int j=0; j<=2*offset; j++){
			if(i) dx[i][j] += dx[i-1][j];
			if(j) dx[i][j] += dx[i][j-1];
			if(i && j) dx[i][j] -= dx[i-1][j-1];
		}
	}
	int ret = 0, px = 1e9, py = 1e9;
	for(int i=0; i<q; i++){
		int m;
	int ret = 0, px = 1e9, py = 1e9;
		scanf("%d",&m);
		for(int j=0; j<=2*offset; j++){
			for(int k=0; k<=2*offset; k++){
				if((j + k) % 2) continue;
				int p = (j + k - offset) / 2;
				int q = j - p;
				if(p <= 0 || q <= 0 || p > a || q > b) continue;
				int sol = get(j-m,j+m,k-m,k+m);
				if(sol > ret){
					ret = sol;
					px = p, py = q;
				}
				else if(sol == ret){
					if(pi(py,px) > pi(q,p)){
						px = p, py = q;
					}
				}
			}
		}
		printf("%d (%d,%d)\n",ret,px,py);
	}
	return 1;
}
int main(){
	while(solve());
}