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
const int MAXC = 20000;

int n;
vector<int> vx[20005], vy[20005];
pi a[1005];

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

char move(int dx, int dy){
	if(dy < 0) return 'S';
	if(dy > 0) return 'N';
	if(dx < 0) return 'W';
	return 'E';
}

void solve(){
	for(int i=0; i<=MAXC; i++){
		vx[i].clear();
		vy[i].clear();
	}
	cin >> n;
	if(n == 0) exit(0);
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		a[i].first += MAXC / 2;
		a[i].second += MAXC / 2;
		vx[a[i].first].push_back(a[i].second);
		vy[a[i].second].push_back(a[i].first);
	}
	for(int i=0; i<=MAXC; i++){
		sort(vx[i].begin(), vx[i].end());
		sort(vy[i].begin(), vy[i].end());
	}
	vector<pi> ord;
	int px = a[0].first, py = a[0].second;
	int l = 0;
	for(int i=0; i<n; i++){
		ord.push_back(pi(px, py));
		if(l == 0){
			int cntx = lower_bound(vx[px].begin(), vx[px].end(), py) - vx[px].begin();
			py = vx[px][cntx^1];
		}
		else{
			int cnty = lower_bound(vy[py].begin(), vy[py].end(), px) - vy[py].begin();
			px = vy[py][cnty^1];
		}
		l ^= 1;
	}
	int area = 0;
	for(int i=2; i<n; i++){
		area += ccw(ord[0], ord[i-1], ord[i]);
	}
	if(area > 0){
		reverse(ord.begin(), ord.end());
		rotate(ord.begin(), --ord.end(), ord.end());
	}
	ord.push_back(ord[0]);
	for(int i=0; i<n; i++){
		putchar(move(ord[i+1].first - ord[i].first, ord[i+1].second - ord[i].second));
	}
	puts("");
}

int main(){
	while(1){
		solve();
	}
}