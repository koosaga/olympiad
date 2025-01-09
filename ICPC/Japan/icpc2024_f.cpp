#include <bits/stdc++.h>
using namespace std;

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T _x=0, T _y=0) : x(_x), y(_y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
};

using ld = double;

using P = Point<ld>;

double ccRadius(const P& A, const P& B, const P& C) {
    return (B-A).dist()*(C-B).dist()*(A-C).dist()/
            abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
    P b = C-A, c = B-A;
    return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

int main(){
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int A, B, C;
    cin >> A >> B >> C;
    vector<int> V {A, B, C};
    double ans = 0;
    for(int it = 0; it < 3; it++){
        double vans = 0;
        P p1(B, A+C);
        P p2(A+B, C);
        P p3(-A, B+C);
        P p4(B+C, -A);

        P p5(-A, -B-C);
        P p6(-B-C, -A);

        P p7(-C, -A-B);
        P p8(-A-C, -B);

        auto solve = [&](P p) -> ld {
            ld res = 1e9;
            res = min(res, (p1-p).dist());
            res = min(res, (p2-p).dist());
            if(p.cross(p3, P(0, C)) <= 0){
                res = min(res, (p - p3).dist());
            }
            if(p.cross(p4, P(B, 0)) >= 0){
                res = min(res, (p - p4).dist());
            }
            if(p.cross(p5, P(0, 0)) >= 0){
                res = min(res, (p - p5).dist());
            }
            if(p.cross(p6, P(0, 0)) <= 0){
                res = min(res, (p - p6).dist());
            }
            if(p.cross(p7, P(0, 0)) <= 0 && p.cross(p7, P(0, -A)) >= 0){
                res = min(res, (p - p7).dist());
            }
            if(p.cross(p8, P(0, 0)) >= 0 && p.cross(p8, P(-A, 0)) <= 0){
                res = min(res, (p - p8).dist());
            }
            return res;
        };
        vans = max(vans, solve(P(0, 0)));
        vector<P> z = {p1, p2, p3, p4, p5, p6};
        for(int a = 0; a < 6; a++){
            for(int b = a+1; b < 6; b++){
                for(int c = b+1; c < 6; c++){
                    P p = ccCenter(z[a], z[b], z[c]);
                    if(p.x >= 0 && p.y >= 0 && p.x <= B && p.y <= C){
                        vans = max(vans, solve(p));
                    }
                }
            }
        }
        swap(A, B);
        swap(B, C);
        ans = max(ans, vans);
    }
    cout << fixed << setprecision(15) << ans << '\n';
}

