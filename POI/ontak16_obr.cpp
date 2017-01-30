#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

struct pnt{
	int x, y, idx;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[2505];

struct line{
	int dx, dy, i1, i2;
};

vector<line> v;
int n, k, rev[2505];

double solve(line l, int x, int y){
	if(x < 0 || y >= n) return 1e9;
	lint d1 = 1ll * l.dy * a[x].x - 1ll * l.dx * a[x].y;
	lint d2 = 1ll * l.dy * a[y].x - 1ll * l.dx * a[y].y;
	return abs(d1 - d2) / hypot(l.dx, l.dy);
}

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++){
		cin >> a[i].x >> a[i].y;
	}
	sort(a, a+n);
	for(int i=0; i<n; i++){
		a[i].idx = i;
		rev[i] = i;
	}
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			v.push_back({a[j].x - a[i].x, a[j].y - a[i].y, a[i].idx, a[j].idx});
		}
	}
	sort(v.begin(), v.end(), [&](const line &a, const line &b){
		return 1ll * a.dx * b.dy - 1ll * b.dx * a.dy;
	});
	double ret = 1e9;
	for(int i=0; i<v.size(); i++){
		int c1 = rev[v[i].i1], c2 = rev[v[i].i2];
		if(c1 > c2) swap(c1, c2);
		ret = min(ret, solve(v[i], c1, c1 + k - 1));
		ret = min(ret, solve(v[i], c2 - k + 1, c2));
		swap(a[c1], a[c2]);
		swap(rev[v[i].i1], rev[v[i].i2]);
	}
	printf("%.10f", ret/2);
}
