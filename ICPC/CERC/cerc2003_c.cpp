#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct pnt{
	int x, y, idx;
}a[250005];

int n;
char str[250005];
int l = 1e9, b = 1e9, e = -1;
char s[22];

void update(pnt a, pnt b){
	if(a.idx > b.idx) swap(a, b);
	int dis = abs(a.x - b.x) + abs(a.y - b.y);
	if(l > dis || (l == dis && pi(a.idx, -b.idx) < pi(::b, e))){
		l = dis;
		::b = a.idx;
		e = b.idx;
		if(a.x < b.x) s[0] = 'E';
		if(a.x > b.x) s[0] = 'W';
		if(a.y < b.y) s[0] = 'N';
		if(a.y > b.y) s[0] = 'S';
	}
}

int main(){
	cin >> n >> str;
	a[0] = {0, 0, 0};
	for(int i=1; i<=n; i++){
		a[i] = a[i-1];
		a[i].idx = i;
		if(str[i-1] == 'N') a[i].y++;
		if(str[i-1] == 'S') a[i].y--;
		if(str[i-1] == 'E') a[i].x++;
		if(str[i-1] == 'W') a[i].x--;
	}
	sort(a, a+n+1, [&](const pnt &a, const pnt &b){
		return pi(a.x, a.y) < pi(b.x, b.y);
	});
	for(int i=1; i<=n; i++){
		if(a[i].x == a[i-1].x && abs(a[i].idx - a[i-1].idx) != 1){
			update(a[i-1], a[i]);
		}
	}
	sort(a, a+n+1, [&](const pnt &a, const pnt &b){
		return pi(a.y, a.x) < pi(b.y, b.x);
	});
	for(int i=1; i<=n; i++){
		if(a[i].y == a[i-1].y && abs(a[i].idx - a[i-1].idx) != 1){
			update(a[i-1], a[i]);
		}
	}
	printf("%d %d %d %s\n",l, b, e, s);
}

