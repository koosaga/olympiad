#include <bits/stdc++.h>
using namespace std;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }

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

    friend bool operator < (const Point& a, const Point& b) { return tie(a.x, a.y) < tie(b.x, b.y); }

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

template<class T> T abs2(T a){
    return a < 0 ? -a : a;
}

template<class T> T gcd(T a, T b){
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    while(a){
        b %= a;
        swap(a, b);
    }
    return b;
}

template<class T> T lcm(T a, T b){
    if(a < 0) a = -a;
    if(b < 0) b = -b;
    return a * (b / gcd(a, b));
}

template<class T> struct fraction {
    T a;
    T b;

    fraction() : a(0), b(1) {}
    fraction(T x) : a(x), b(1) {}
    fraction(T _a, T _b) : a(_a), b(_b) { reduce(); }
    friend std::ostream& operator << (std::ostream& out, const fraction& n) { return out << n.a << '/' << n.b; }

    fraction neg() const {
        fraction res {-a, b};
        return res;
    }
    friend fraction neg(const fraction& m) { return m.neg(); }

    fraction abs() const {
        fraction res {abs2(a), abs2(b)};
        return res;
    }
    friend fraction abs(const fraction& m) { return m.abs(); }

    fraction operator- () const {
        return neg();
    }
    fraction operator+ () const {
        return fraction(*this);
    }

    friend bool operator == (const fraction& x, const fraction& y){
        return x.a * y.b == x.b * y.a;
    }
    friend bool operator != (const fraction& x, const fraction& y){
        return x.a * y.b != x.b * y.a;
    }
    friend bool operator < (const fraction& x, const fraction& y){
        return x.a * y.b < x.b * y.a;
    }
    friend bool operator <= (const fraction& x, const fraction& y){
        return x.a * y.b <= x.b * y.a;
    }
    friend bool operator > (const fraction& x, const fraction& y){
        return x.a * y.b > x.b * y.a;
    }
    friend bool operator >= (const fraction& x, const fraction& y){
        return x.a * y.b >= x.b * y.a;
    }

    void reduce(){
        T g = gcd(abs2(a), abs2(b));
        a /= g;
        b /= g;
        if(b < 0) { a = -a; b = -b; }
    }

    fraction& operator += (const fraction& o){
        *this = {a * o.b + b * o.a, b * o.b};
        reduce();
        return *this;
    }
    fraction& operator -= (const fraction& o){
        *this = {a * o.b - b * o.a, b * o.b};
        reduce();
        return *this;
    }
    fraction& operator *= (const fraction& o){
        *this = {a * o.a, b * o.b};
        reduce();
        return *this;
    }
    fraction& operator /= (const fraction& o){
        *this = {a * o.b, b * o.a};
        reduce();
        return *this;
    }
    friend fraction operator + (const fraction& a, const fraction& b) { return fraction(a) += b; }
    friend fraction operator - (const fraction& a, const fraction& b) { return fraction(a) -= b; }
    friend fraction operator * (const fraction& a, const fraction& b) { return fraction(a) *= b; }
    friend fraction operator / (const fraction& a, const fraction& b) { return fraction(a) /= b; }
};

template<class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
    auto d = cross((e1 - s1), (e2 - s2));
    if (d == 0) // if parallel
        return {-(cross3(s1, e1, s2) == 0), P(0, 0)};
    auto p = cross3(s2, e1, e2), q = cross3(s2, e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

// using i128 = int64_t;
using i128 = long long;
using frac = fraction<i128>;

using ll = int64_t;
using P = Point<frac>;

using Pi = Point<i128>;


using ld = double;

using Pd = Point<ld>;


#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
// typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


vector<Pd> convexHull(vector<Pd> pts) {
    if (sz(pts) <= 1) return pts;
    sort(all(pts));
    vector<Pd> h(sz(pts)+1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(all(pts)))
        for (Pd p : pts) {
            while (t >= s + 2 && cross3(h[t-2], h[t-1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
template<class T>
T polygonArea2(vector<Point<T>>& v) {
    T a = cross(v.back(), v[0]);
    rep(i,0,sz(v)-1) a += cross(v[i], v[i+1]);
    return a;
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int N;
    cin >> N;
    vector<Pi> Ai(N);
    vector<P> A(N);
    for(int i = 0; i < N; i++){
        ll x, y;
        cin >> x >> y;
        A[i] = P(frac(x), frac(y));
        Ai[i] = Pi(x, y);
    };
    vector<P> cands;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cands.push_back((A[i] + A[j]) / 2);
        }
    }
    vector<pair<P, P> > segs;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            segs.push_back({(A[i] + A[j]) / 2, (A[i] + A[(j+1) % N]) / 2});
        }
    }
    for(auto [s1, e1] : segs){
        cands.push_back(s1);
        cands.push_back(e1);
        for(auto [s2, e2] : segs){
            cands.push_back(lineInter(s1, e1, s2, e2).second);
        }
    }
    ld ans = 1e18;
    bool works = false;
    for(P c : cands){
        i128 S = lcm(c.x.b, c.y.b);

        i128 cx = c.x.a * (S / c.x.b);
        i128 cy = c.y.a * (S / c.y.b);
        vector<Pi> g;
        for(Pi p : Ai){
            g.push_back(p * S);
            g.push_back(Pi(cx, cy) * 2 - p * S);
        }
        sort(g.begin(), g.end());
        g.resize(unique(g.begin(), g.end()) - g.begin());
        i128 xmin = g.front().x;
        i128 xmax = g.back().x;
        for(Pi p : g) xmin = min(p.x, xmin);
        for(Pi p : g) xmax = max(p.x, xmax);

        vector<Pi> upper_hull;
        vector<Pi> lower_hull;
        int i = 0;
        while(i < (int)g.size()){
            int j = i;
            while(j+1 < (int)g.size() && g[j].x == g[j+1].x){
                j++;
            }
            {
                Pi lower = g[i];
                while(lower_hull.size() >= 2){
                    Pi a = lower_hull[lower_hull.size() - 2];
                    Pi b = lower_hull[lower_hull.size() - 1];
                    if(cross(lower-b, a-b) < 0){
                        lower_hull.pop_back();
                    } else break;
                }
                lower_hull.push_back(lower);
            }
            {
                Pi upper = g[j];
                while(upper_hull.size() >= 2){
                    Pi a = upper_hull[upper_hull.size() - 2];
                    Pi b = upper_hull[upper_hull.size() - 1];
                    if(cross(upper-b, a-b) > 0){
                        upper_hull.pop_back();
                    } else break;
                }
                upper_hull.push_back(upper);
            }
            // try to insert lower into lower hull
            i = j+1;
        }
        vector<Pi> hull_points;
        for(Pi p : g){
            if(p.x == xmin || p.x == xmax){
                hull_points.push_back(p);
            }
        }
        hull_points.insert(hull_points.end(), upper_hull.begin(), upper_hull.end());
        hull_points.insert(hull_points.end(), lower_hull.begin(), lower_hull.end());
        sort(hull_points.begin(), hull_points.end());
        hull_points.resize(unique(hull_points.begin(), hull_points.end()) - hull_points.begin());
        if(hull_points.size() == g.size()){
            works = true;
            Pd cd = Pd(ld(c.x.a) / ld(c.x.b), ld(c.y.a) / ld(c.y.b));
            vector<Pd> pts;
            for(Pi p : Ai){
                pts.push_back(Pd(p.x, p.y));
                pts.push_back(cd * 2 - Pd(p.x, p.y));
            }
            vector<Pd> hull_double = convexHull(pts);
            ld area = abs(polygonArea2(hull_double)) / 2;
            ans = min(ans, area);
        }
    }
    if(!works){
        cout << -1 << '\n';
    } else {
        cout << fixed << setprecision(10);
        cout << ans << '\n';
    }
}