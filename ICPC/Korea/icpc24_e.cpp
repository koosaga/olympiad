#include <bits/stdc++.h>
using namespace std;


template <typename T> struct Point {
public:
	T x, y;
	Point() : x(0), y(0) {}
	Point(T x_, T y_) : x(x_), y(y_) {}
	template <typename U> explicit Point(const Point<U>& p) : x(p.x), y(p.y) {}
	Point(const std::pair<T, T>& p) : x(p.first), y(p.second) {}
	Point(const std::complex<T>& p) : x(real(p)), y(imag(p)) {}
	explicit operator std::pair<T, T> () const { return std::pair<T, T>(x, y); }
	explicit operator std::complex<T> () const { return std::complex<T>(x, y); }

	friend std::ostream& operator << (std::ostream& o, const Point& p) { return o << '(' << p.x << ',' << p.y << ')'; }
	friend std::istream& operator >> (std::istream& i, Point& p) { return i >> p.x >> p.y; }
	friend bool operator == (const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
	friend bool operator != (const Point& a, const Point& b) { return !(a==b); }

	Point operator + () const { return Point(+x, +y); }
	Point operator - () const { return Point(-x, -y); }

	Point& operator += (const Point& p) { x += p.x, y += p.y; return *this; }
	Point& operator -= (const Point& p) { x -= p.x, y -= p.y; return *this; }
	Point& operator *= (const T& t) { x *= t, y *= t; return *this; }
	Point& operator /= (const T& t) { x /= t, y /= t; return *this; }

	friend Point operator + (const Point& a, const Point& b) { return Point(a.x+b.x, a.y+b.y); }
	friend Point operator - (const Point& a, const Point& b) { return Point(a.x-b.x, a.y-b.y); }
	friend Point operator * (const Point& a, const T& t) { return Point(a.x*t, a.y*t); }
	friend Point operator * (const T& t ,const Point& a) { return Point(t*a.x, t*a.y); }
	friend Point operator / (const Point& a, const T& t) { return Point(a.x/t, a.y/t); }

	T dist2() const { return x * x + y * y; }
	auto dist() const { return std::sqrt(dist2()); }
	Point unit() const { return *this / this->dist(); }
	auto angle() const { return std::atan2(y, x); }

	T int_norm() const { return __gcd(x,y); }
	Point int_unit() const { if (!x && !y) return *this; return *this / this->int_norm(); }

	// Convenient free-functions, mostly for generic interop
	friend auto norm(const Point& a) { return a.dist2(); }
	friend auto abs(const Point& a) { return a.dist(); }
	friend auto unit(const Point& a) { return a.unit(); }
	friend auto arg(const Point& a) { return a.angle(); }
	friend auto int_norm(const Point& a) { return a.int_norm(); }
	friend auto int_unit(const Point& a) { return a.int_unit(); }

	Point perp_cw() const { return Point(y, -x); }
	Point perp_ccw() const { return Point(-y, x); }

	friend T dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
	friend T cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
	friend T cross3(const Point& a, const Point& b, const Point& c) { return cross(b-a, c-a); }

	// Complex numbers and rotation
	friend Point conj(const Point& a) { return Point(a.x, -a.y); }

	// Returns conj(a) * b
	friend Point dot_cross(const Point& a, const Point& b) { return Point(dot(a, b), cross(a, b)); }
	friend Point cmul(const Point& a, const Point& b) { return dot_cross(conj(a), b); }
	friend Point cdiv(const Point& a, const Point& b) { return dot_cross(b, a) / b.norm(); }

	// Must be a unit vector; otherwise multiplies the result by abs(u)
	Point rotate(const Point& u) const { return dot_cross(conj(u), *this); }
	Point unrotate(const Point& u) const { return dot_cross(u, *this); }

	friend bool lex_less(const Point& a, const Point& b) {
		return std::tie(a.x, a.y) < std::tie(b.x, b.y);
	}

	friend bool same_dir(const Point& a, const Point& b) { return cross(a,b) == 0 && dot(a,b) > 0; }

	// check if 180 <= s..t < 360
	friend bool is_reflex(const Point& a, const Point& b) { auto c = cross(a,b); return c ? (c < 0) : (dot(a, b) < 0); }

	// operator < (s,t) for angles in [base,base+2pi)
	friend bool angle_less(const Point& base, const Point& s, const Point& t) {
		int r = is_reflex(base, s) - is_reflex(base, t);
		return r ? (r < 0) : (0 < cross(s, t));
	}

	friend auto angle_cmp(const Point& base) {
		return [base](const Point& s, const Point& t) { return angle_less(base, s, t); };
	}
	friend auto angle_cmp_center(const Point& center, const Point& dir) {
		return [center, dir](const Point& s, const Point& t) -> bool { return angle_less(dir, s-center, t-center); };
	}

	// is p in [s,t] taken ccw? 1/0/-1 for in/border/out
	friend int angle_between(const Point& s, const Point& t, const Point& p) {
		if (same_dir(p, s) || same_dir(p, t)) return 0;
		return angle_less(s, p, t) ? 1 : -1;
	}
};

using ll = int64_t;
using P = Point<ll>;

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);

	int N;
	cin >> N;
	vector<P> pts;
	P pt(0, 0);
	for(int i = 0; i < N; i++){
		if(i % 2 == 1){
			cin >> pt.y;
		} else {
			cin >> pt.x;
		}
		pts.push_back(pt);
	}
	using ld = double;
	vector<vector<ld> > dist(2, vector<ld>(N, 1e18));
	P start, end;
	cin >> start >> end;
	auto process = [&](P S, bool flip) -> vector<ld> {
		if(flip){
			S.y = -S.y;
			for(auto& p : pts) p.y = -p.y;
		}
		vector<ld> res(N, 1e18);
		for(int dir = 0; dir < 2; dir++){
			vector<P> hull;
			vector<ld> hull_dist;
			hull.push_back(S);
			hull_dist.push_back(0);
			for(int i = 0; i < N; i++){
				if(pts[i].x < S.x) continue;
				P cur = pts[i];
				if(!hull.empty() && cur == hull.back()) continue;
				while(hull.size() >= 2 && cross3(hull[hull.size()-2], hull.back(), cur) >= 0){
					hull.pop_back();
					hull_dist.pop_back();
				}
				ld D = (cur - hull.back()).dist() + hull_dist.back();
				res[i] = min(res[i], D);
				if(cur != hull.back()){
					hull.push_back(cur);
					hull_dist.push_back(D);
				}
			}
			reverse(res.begin(), res.end());
			reverse(pts.begin(), pts.end());
			S.x = -S.x;
			for(auto& p : pts) p.x = -p.x;
		}
		if(flip){
			S.y = -S.y;
			for(auto& p : pts) p.y = -p.y;
		}
		return res;
	};
	ld d_front = 1e18, d_back = 1e18;
	if(start.y <= 0){
		d_front = (start - pts.front()).dist();
		d_back = (start - pts.back()).dist();
	} else {
		vector<ld> res = process(start, false);
		d_front = res[0];
		d_back = res[N-1];
	}
	d_front = min(d_front, d_back + (pts.back() - pts.front()).dist());
	d_back = min(d_back, d_front + (pts.back() - pts.front()).dist());
	{
		vector<ld> dist_front = process(pts.front(), false);
		for(int i = 0; i < N; i++){
			dist[0][i] = min(dist[0][i], dist_front[i] + d_front);
		}
	}
	{
		vector<ld> dist_back = process(pts.back(), false);
		for(int i = 0; i < N; i++){
			dist[0][i] = min(dist[0][i], dist_back[i] + d_back);
		}
	}
	if(start.y >= 0 || start.x <= pts.front().x || start.x >= pts.back().x){
		vector<ld> dist_real = process(start, false);
		for(int i = 0; i < N; i++){
			dist[0][i] = min(dist[0][i], dist_real[i]);
		}
	}
	dist[1] = process(end, true);
	ld ans = 1e18;
	for(int i = 0; i < N; i++){
		ans = min(ans, dist[0][i] + dist[1][i]);
	}
	cout << fixed << setprecision(15) << ans << '\n';
}
