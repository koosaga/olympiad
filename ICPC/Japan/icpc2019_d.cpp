#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long long ll;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 405;

struct vec3{
	ll x, y, z;
	vec3(): x(0), y(0), z(0) {}
	vec3(ll a, ll b, ll c): x(a), y(b), z(c) {}
	vec3 operator*(const vec3& v) const{ return vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	vec3 operator-(const vec3& v) const{ return vec3(x-v.x, y-v.y, z-v.z); }
	vec3 operator-() const{ return vec3(-x, -y, -z); }
	ll dot(const vec3 &v) const{ return x*v.x+y*v.y+z*v.z; }
}a[MAXN];

lint dist(vec3 a, vec3 b){
	return (a - b).dot(a - b);
}

int func[MAXN];
int n;
vector<int> gph[MAXN];
using pi = pair<vector<lint>, int>;

bool iso(vector<pi> v1, vector<pi> v2){
	sort(all(v1));
	sort(all(v2));
	for(int i=0; i<n; i++){
		if(v1[i].first == v2[i].first){
			func[v1[i].second] = v2[i].second;
		}
		else return 0;
	}
	vector<pair<int, int>> edg1, edg2;
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]) edg1.emplace_back(func[i], func[j]);
		for(auto &j : gph[i + n]) edg2.emplace_back(i + n, j);
	}
	sort(all(edg1));
	sort(all(edg2));
	return edg1 == edg2;
}

bool TRY(int x1, int y1, int z1, int x2, int y2, int z2){
	vector<pi> v1, v2;
	auto p1 = (a[y1] - a[x1]) * (a[z1] - a[x1]);
	auto p2 = (a[y2] - a[x2]) * (a[z2] - a[x2]);
	if(p1.dot(p1) && !p2.dot(p2)) return 0;
	if(!p1.dot(p1) && p2.dot(p2)) return 0;
	int mag1 = dist(a[y1], a[z1]);
	int mag2 = dist(a[y2], a[z2]); 
	for(int i=1; i<=n; i++){
		vector<lint> v = {
			dist(a[x1], a[i]) * mag2, 
			dist(a[y1], a[i]) * mag2, 
			dist(a[z1], a[i]) * mag2, 
			p1.dot(a[i] - a[x1])
		};
		if(v[3] != 0) v[3] /= abs(v[3]);
		v1.emplace_back(v, i);
	}
	for(int i=n+1; i<=n+n; i++){
		vector<lint> v = {
			dist(a[x2], a[i]) * mag1, 
			dist(a[y2], a[i]) * mag1, 
			dist(a[z2], a[i]) * mag1, 
			p2.dot(a[i] - a[x2])
		};
		if(v[3] != 0) v[3] /= abs(v[3]);
		v2.emplace_back(v, i);
	}
	return iso(v1, v2);
}

int main(){
	cin >> n;
	for(int i=0; i<=n; i+=n){
		for(int j=1; j<=n; j++){
			cin >> a[i + j].x >> a[i + j].y >> a[i + j].z;
		}
		for(int j=1; j<n; j++){
			int x, y; cin >> x >> y;
			gph[x].push_back(y);
			gph[y].push_back(x);
		}
	}
	int sx = -1, sy = -1, sz = -1;
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]){
			for(auto &k : gph[i]){
				if(j == k) break;
				auto pl = (a[j] - a[i]) * (a[k] - a[i]);
				if(sx == -1 || pl.dot(pl)){
					sx = i;
					sy = j;
					sz = k;
				}
			}
		}
	}
	int ans = 0;
	for(int i=n+1; i<=n+n; i++){
		for(auto &j : gph[i]){
			for(auto &k : gph[i]){
				if(j != k && TRY(sx, sy, sz, i, j, k)) ans++;
			}
		}
	}
	cout << ans << endl;
}


