#include<bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3005;

struct point{
	int x, y; char dir;
}a[MAXN];
int n, ox[MAXN], oy[MAXN], px[MAXN], py[MAXN];
int sx[MAXN + 1], sy[MAXN + 1], rx[MAXN], ry[MAXN];

bool cmpx(int i, int j){
	if(a[i].x != a[j].x) return a[i].x < a[j].x;
	return a[i].y < a[j].y;
}

bool cmpy(int i, int j){
	if(a[i].y != a[j].y) return a[i].y < a[j].y;
	return a[i].x < a[j].x;
}

int fsx(int x){ return sx[x] == x ? x : sx[x] = fsx(sx[x]); }
int fsy(int x){ return sy[x] == x ? x : sy[x] = fsy(sy[x]); }

int frx(int x){
	if(x < 0) return -1;
	return rx[x] == x ? x : rx[x] = frx(rx[x]);
}

int fry(int x){
	if(x < 0) return -1;
	return ry[x] == x ? x : ry[x] = fry(ry[x]);
}

int f(int x){
	for(int i=0; i<=n; i++) sx[i] = sy[i] = i;
	for(int i=0; i<n; i++) rx[i] = ry[i] = i;
	int cur = x, ret = 0;
	while(true){
		sx[px[cur]] = fsx(px[cur] + 1);
		sy[py[cur]] = fsy(py[cur] + 1);
		rx[px[cur]] = frx(px[cur] - 1);
		ry[py[cur]] = fry(py[cur] - 1);
		ret++;
		if(a[cur].dir == '>'){
			int l = fsx(px[cur]);
			if(l < n && a[ox[l]].x == a[cur].x) cur = ox[l];
			else break;
		}
		if(a[cur].dir == '<'){
			int l = frx(px[cur]);
			if(l >= 0 && a[ox[l]].x == a[cur].x) cur = ox[l];
			else break;
		}
		if(a[cur].dir == 'v'){
			int l = fsy(py[cur]);
			if(l < n && a[oy[l]].y == a[cur].y) cur = oy[l];
			else break;
		}
		if(a[cur].dir == '^'){
			int l = fry(py[cur]);
			if(l >= 0 && a[oy[l]].y == a[cur].y) cur = oy[l];
			else break;
		}
	}
	return ret;
}

int main(){	
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].x >> a[i].y >> a[i].dir;
		swap(a[i].x, a[i].y);
		ox[i] = oy[i] = i;
	}
	sort(ox, ox + n, cmpx);
	sort(oy, oy + n, cmpy);
	for(int i=0; i<n; i++){
		px[ox[i]] = i;
		py[oy[i]] = i;
	}
	int ret = 0;
	for(int i=0; i<n; i++) ret = max(ret, f(i));
	cout << ret << endl;
}