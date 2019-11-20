#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

struct sphere{
	int x, y, z, r;
	bool operator<(const sphere &s)const{
		return r > s.r;
	}
}a[MAXN];

int n, k;
vector<int> ret;

lint sqr(lint x){ return x * x; }

bool cross(sphere &p, sphere &q, int r){
	lint dis = sqr(p.x - q.x) + sqr(p.y - q.y) + sqr(p.z - q.z);
	return dis <= sqr(p.r + q.r + 2 * r);
}

int dist(sphere &p, sphere &q){
	int s = 0, e = 2e6;
	while(s != e){
		int m = (s+e)/2;
		if(cross(p, q, m)) e = m;
		else s = m + 1;
	}
	return s;
}

bool trial(int r){
	vector<pair<lint, int>> v;
	ret.clear();
	int thres = 1e9;
	for(int i=0; i<n; i++){
		int cur = a[i].r + r;
		if(thres > 4 * cur){
			thres = 2 * cur;
			v.clear();
			for(int j=i+1; j<n; j++){
				int px = a[j].x / thres;
				int py = a[j].y / thres;
				int pz = a[j].z / thres;
				lint code = ((1ll * px) << 42) | ((1ll * py) << 21) | pz;
				v.emplace_back(code, j);
			}
			sort(all(v));
		}
		int px = a[i].x / thres;
		int py = a[i].y / thres;
		int pz = a[i].z / thres;
		for(int x = max(0, px - 1); x <= px + 1; x++){
			for(int y = max(0, py - 1); y <= py + 1; y++){
				lint codes = ((1ll * x) << 42) | ((1ll * y) << 21) | max(0, pz - 1);
				lint codee = ((1ll * x) << 42) | ((1ll * y) << 21) | (pz + 1);
				auto it = lower_bound(all(v), make_pair(codes, -1));
				while(it != v.end() && it->first <= codee){
					int l = (it++)->second;
					if(l > i && cross(a[i], a[l], r)){
						ret.push_back(dist(a[i], a[l]));
						if(sz(ret) >= k) return 1;
					}
				}
			}
		}
	}
	return 0;
}

void solve(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&a[i].x,&a[i].y,&a[i].z,&a[i].r);
		a[i].x <<= 1;
		a[i].y <<= 1;
		a[i].z <<= 1;
		a[i].r <<= 1;
	}
	sort(a, a + n);
	int s = 0, e = 2e6;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	if(s > 0) trial(s - 1);
	else ret.clear();
	sort(all(ret));
	while(sz(ret) < k) ret.push_back(s);
	for(auto &i : ret) printf("%d ", i);
	puts("");
}

int main(){	
//	freopen("input.txt", "rb", stdin);
//	freopen("output.txt", "wb", stdout);
	int t;
	scanf("%d",&t);
	for(int i=0; i<t; i++) solve();
}
