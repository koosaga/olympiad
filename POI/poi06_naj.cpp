#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct pnt{
	int x, y, v;
};

int ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 - dy1 * dx2;
}

int n, m;
pi a[605];
pnt b[10005];
int cst[605][605];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i].first >> a[i].second;
	reverse(a, a+n);
	cin >> m;
	for(int i=0; i<m; i++) cin >> b[i].x >> b[i].y >> b[i].v;
	for(int i=0; i<n; i++){
		vector<pnt> vec;
		for(int j=0; j<m; j++){
			if(pi(b[j].x, b[j].y) != a[i]) vec.push_back(b[j]);
		}
		sort(vec.begin(), vec.end(), [&](const pnt &p, const pnt &q){
			return ccw(a[i], pi(p.x, p.y), pi(q.x, q.y)) > 0;
		});
		int pt = 0, ans = 0;
		for(int j=1; j<n; j++){
			while(pt < vec.size() && ccw(a[i], pi(vec[pt].x, vec[pt].y), a[(i+j)%n]) > 0){
				ans += vec[pt].v;
				pt++;
			}
			cst[i][(i+j)%n] = ans;
		}
	}
	int ret = 1e9;
	for(int i=0; i<n; i++){
		for(int j=i+1; j<n; j++){
			for(int k=j+1; k<n; k++){
				ret = min(ret, cst[i][j] + cst[j][k] + cst[k][i]);
			}
		}
	}
	ret = -ret;
	for(int i=0; i<m; i++) ret += b[i].v;
	cout << ret;
}
