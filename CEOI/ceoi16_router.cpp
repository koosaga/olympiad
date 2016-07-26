#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, edg, deg;

vector<pi> v;

int norm(int x){
	if(x < 0) return -x;
	return x + 2 * n;
}

struct flo{
	int sx, ex, sy, ey, idx;
};

flo a[4][1005];

bool intersect(flo a, flo b){
	return max(a.sx, b.sx) <= min(a.ex, b.ex) && max(a.sy, b.sy) <= min(a.ey, b.ey);
}

int main(){
	cin >> n >> edg >> deg;	
	int piv = 0;
	for(int j=1; j<=1000; j++){
		a[0][j] = {10 * j - 9, 10 * j, 1, 10000, ++piv};
	}
	int st = 1, ed = 100;
	int st2 = 1, ed2 = 1000;
	for(int j=1; j<=1000; j++){
		a[1][j] = {st, ed, st2, ed2, ++piv};
		st += 100;
		ed += 100;
		if(st > 10000){
			st = 1;
			ed = 100;
			st2 += 1000;
			ed2 += 1000;
		}
	}
	st = 1, ed = 1000, st2 = 1, ed2 = 100;
	for(int j=1; j<=1000; j++){
		a[2][j] = {st, ed, st2, ed2, ++piv};
		st += 1000;
		ed += 1000;
		if(st > 10000){
			st = 1;
			ed = 1000;
			st2 += 100;
			ed2 += 100;
		}
	}
	for(int j=1; j<=1000; j++){
		a[3][j] = {1, 10000, 10*j-9, 10*j, ++piv};
	}
	for(int i=1; i<=n; i++){
		v.push_back({-i, (i+9)/10});
		v.push_back({3000 + (i+9)/10, -i-n});
	}
	for(int i=0; i<3; i++){
		for(int j=1; j<=1000; j++){
			for(int k=1; k<=1000; k++){
				if(intersect(a[i][j], a[i+1][k])){
					v.push_back({a[i][j].idx, a[i+1][k].idx});
				}
			}
		}
	}
	printf("%d %d\n", 2 * n + 4000, v.size());
	for(auto &i : v){
		printf("%d %d\n", norm(i.first), norm(i.second));
	}
}
