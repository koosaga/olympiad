#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

template<class T> struct Point3D {
	typedef Point3D P;
	typedef const P& R;
	T x, y, z;
	explicit Point3D(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(R p) const {
		return tie(x, y, z) < tie(p.x, p.y, p.z); }
	bool operator==(R p) const {
		return tie(x, y, z) == tie(p.x, p.y, p.z); }
	P operator+(R p) const { return P(x+p.x, y+p.y, z+p.z); }
	P operator-(R p) const { return P(x-p.x, y-p.y, z-p.z); }
	P operator*(T d) const { return P(x*d, y*d, z*d); }
	P operator/(T d) const { return P(x/d, y/d, z/d); }
	T dot(R p) const { return x*p.x + y*p.y + z*p.z; }
	P cross(R p) const {
		return P(y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x);
	}
	T dist2() const { return x*x + y*y + z*z; }
	double dist() const { return sqrt((double)dist2()); }
	//Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
	double phi() const { return atan2(y, x); }
	//Zenith angle (latitude) to the z-axis in interval [0, pi]
	double theta() const { return atan2(sqrt(x*x+y*y),z); }
	P unit() const { return *this/(T)dist(); } //makes dist()=1
	//returns unit vector normal to *this and p
	P normal(P p) const { return cross(p).unit(); }
	//returns point rotated 'angle' radians ccw around axis
	P rotate(double angle, P axis) const {
		double s = sin(angle), c = cos(angle); P u = axis.unit();
		return u*dot(u)*(1-c) + (*this)*c - cross(u)*s;
	}
};

using punk = Point3D<llf>;
const llf ERAD = 6370;
const llf eps = 1e-9;
const llf PI = acos(-1);
const int MAXN = 800;

// circle: center a, radius R
// plane: perpendicular to perp, and passes center
// shoutout to benq

llf dot(punk a, punk b){ return a.dot(b); }
punk cross(punk a, punk b){ return a.cross(b); }
llf dist(punk a, punk b){ return acos(dot(a, b)); }
llf abs(punk a){ return a.dist(); }
punk unit(punk a){ return a.unit(); }

vector<punk> planeCircleIsect(punk a, punk perp, llf R) { 
	punk dif = a-perp*dot(a,perp);
	llf x = cos(R)/abs(dif);
	if (x < -1 || x > 1) return {};
	dif = unit(dif);
	punk oops = cross(dif,perp);
	llf y = sqrt(1-x*x);
	return {dif*x+oops*y,dif*x-oops*y};
}

vector<punk> V;
int n;
llf r;

bool visible(punk a, punk b){
	if (abs(a-b) <= eps) return 1;
	// perp cap sphere => circle that contains path between a / b
	// essentially, this is the z-axis
	punk perp = cross(a,b).unit();
	punk yaxis = cross(perp,a).unit();
	punk xaxis = a.unit();
	auto get_angle = [&](punk p) {
		llf X = dot(xaxis, p);
		llf Y = dot(yaxis, p);
		llf ang = atan2(Y, X);
		if (ang < -eps) ang += 2 * PI;
		return ang;
	};
	auto get_point = [&](llf ang) {
		return xaxis * cos(ang) + yaxis * sin(ang);
	};
	llf hi = get_angle(b);
	vector<llf> args = {0, hi};
	for(int i = 0; i < n; i++){
		auto val = planeCircleIsect(V[i], perp, r);
		for(auto &j : val){
			llf foo = get_angle(j);
			if(foo < hi) args.push_back(foo);
		}
	}
	sort(all(args));
	for(int i = 1; i < sz(args); i++){
		punk cand = get_point((args[i - 1] + args[i]) / 2);
		bool good = 0;
		for(int j = 0; j < n; j++){
			if(dist(cand, V[j]) < r + eps){
				good = 1;
				break;
			}
		}
		if(!good) return 0;
	}
	return 1;
}

llf adj[MAXN][MAXN];
llf comp[30][30], tmp[30][30];

void solve(){
	r /= ERAD;
	for(int i = 0; i < n; i++){
		llf phi, theta; cin >> phi >> theta;
		phi *= PI/180; 
		theta *= PI/180;
		V.emplace_back(cos(theta) * cos(phi), cos(theta) * sin(phi), sin(theta));
	}
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			auto res = planeCircleIsect(V[i], (V[j] - V[i]).unit(), r);
			for(auto &k : res) V.push_back(k);
		}
	}
	for(int i = 0; i < sz(V); i++){
		for(int j = 0; j < i; j++){
			if(visible(V[i], V[j])){
				adj[i][j] = adj[j][i] = ERAD * dist(V[i], V[j]);
			} else{
				adj[i][j] = adj[j][i] = 1e18;
			}
		}
		adj[i][i] = 0;
	}
	for(int s = 0; s < n; s++){
		using pi = pair<llf, int>;
		vector<int> vis(sz(V));
		vector<llf> dist(sz(V), 1e18);
		dist[s] = 0;
		while(true){
			pi val(1e18, -1);
			for(int j = 0; j < sz(V); j++){
				if(!vis[j]) val = min(val, pi(dist[j], j));
			}
			if(val.second == -1) break;
			int x = val.second;
			vis[x] = 1;
			for(int j = 0; j < sz(V); j++){
				dist[j] = min(dist[j], dist[x] + adj[x][j]);
			}
		}
		for(int i = 0; i < n; i++){
			comp[s][i] = dist[i];
		}
	}
	int q; cin >> q;
	while(q--){
		int x, y; llf c;
		cin >> x >> y >> c;
		x--; y--;
		memcpy(tmp, comp, sizeof(tmp));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(comp[i][j] > c + eps) comp[i][j] = 1e18;
			}
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				for(int k = 0; k < n; k++){
					comp[j][k] = min(comp[j][k], comp[j][i] + comp[i][k]);
				}
			}
		}
		llf ans = comp[x][y];
		if(ans > 1e17) puts("impossible");
		else printf("%.3Lf\n", ans);
		memcpy(comp, tmp, sizeof(tmp));
	}
}

int main(){
	int tc = 0;
	while(cin >> n >> r){
		printf("Case %d:\n", ++tc);
		solve();
		V.clear();
	}
}
