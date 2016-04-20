#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
  
struct pnt{
	int x, y, c;
}a[3005];
 
int n;
 
lint ccw(pnt a, pnt b, pnt c){
	int dx1 = b.x - a.x;
	int dy1 = b.y - a.y;
	int dx2 = c.x - a.x;
	int dy2 = c.y - a.y;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}
 
int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].x >> a[i].y >> a[i].c;
	}
	lint ret = 0;
	for(int i=0; i<n; i++){
		int cl[3] = {}, cr[3] = {};
		vector<pnt> v;
		for(int j=0; j<n; j++){
			if(i != j) v.push_back(a[j]);
		}
		sort(v.begin(), v.end(), [&](const pnt &p, const pnt &q){
			if(p.y == a[i].y && p.x > a[i].x) return true;
			if(q.y == a[i].y && q.x > a[i].x) return false;
			if(1ll * (a[i].y - p.y) * (a[i].y - q.y) <= 0) return p.y > q.y;
			return ccw(a[i], p, q) > 0;
		});
		for(int i=0; i<n-1; i++){
			cr[v[i].c]++;
			v.push_back(v[i]);
		}
		int p = 0;
		for(int j=0; j<n-1; j++){
			while(p < n-1+j && ccw(a[i], v[j], v[p]) >= 0){
				cl[v[p].c]++;
				cr[v[p].c]--;
				p++;
			}
			cl[v[j].c]--;
			lint tret = 1;
			for(int k=0; k<3; k++){
				if(a[i].c != k) tret *= cl[k];
				if(v[j].c != k) tret *= cr[k];
			}
			ret += tret;
			cr[v[j].c]++;
		}
	}
	cout << ret / 2;
}