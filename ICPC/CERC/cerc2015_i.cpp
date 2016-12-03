#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
typedef vector<int> vi;
const int n = 500;

bool chk[505][505];
int rad[505][505];

double dist(pi a, pi b){
	return hypot(b.first - a.first, b.second - a.second);
}

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return abs(dx1 * dy2 - dy1 * dx2);
}

lint dot(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dx2 + dy1 * dy2;
}

int inside(pi s, pi e, pi x, int p){
	if(dot(s, e, x) <= 0 || dot(e, s, x) <= 0){
		double d = min(dist(s, x), dist(e, x));
		return d <= 0.1 * p;
	}
	double d = dist(s, e);
	double a = ccw(s, e, x);
	return a / d <= 0.1 * p;
}

int main(){
	int q;
	scanf("%d",&q);
	while(q--){
		int x, y, d;
		scanf("%d %d 0.%d",&x,&y,&d);
		chk[x][y] = 1;
		rad[x][y] = d;
	}
	scanf("%d",&q);
	while(q--){
		int x1, y1, x2, y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		if(pi(x1, y1) > pi(x2, y2)){
			swap(x1, x2);
			swap(y1, y2);
		}
		pi st = pi(x1, y1);
		pi ed = pi(x2, y2);
		int ret = 0;
		if(x1 == x2){
			for(int i=y1; i<=y2; i++){
				if(chk[x1][i] && inside(st, ed, pi(x1, i), rad[x1][i])){
					ret++;
				}
			}
		}
		else{
			for(int i=x1; i<=x2; i++){
				int cen = (int)floor(y1 + 1e-9 + (1.0 * (y2 - y1) * (i - x1)) / (x2 - x1));
				for(int j=cen+1; j<=n; j++){
					if(!inside(st, ed, pi(i, j), 10)) break;
					if(chk[i][j] && inside(st, ed, pi(i, j), rad[i][j])) ret++;
				}
				for(int j=cen; j>=1; j--){
					if(!inside(st, ed, pi(i, j), 10)) break;
					if(chk[i][j] && inside(st, ed, pi(i, j), rad[i][j])) ret++;
				}
			}
		}
		printf("%d\n", ret);
	}
}