#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = double;
using pi = pair<lint, lint>;
using point = complex<llf>;
const double eps = 1e-6;

const int mod = 1e9 + 7;

llf ccw(point a, point b){
	return (conj(a) * b).imag();
}

llf dot(point a, point b){
	return (conj(a) * b).real();
}

llf ccw(point a, point b, point c){
	return ccw(b - a, c - a);
}

int sgn(llf x){
	if(fabs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
}

point insec(point a, point b, point c, point d){
	llf a0 = ccw(a, b, c), a1 = ccw(a, b, d);
	return (d * a0 - c * a1) / (a0 - a1);
}

point circleLine(point a, point b){
	b -= a;
	llf A = dot(b, b);
	llf B = dot(a, b);
	llf C = dot(a, a) - 1;
	llf D = B * B - A * C;
	D = max(D, (llf)0.0);
	point p1 = a + b * (-B + sqrt(D)) / A;
	return p1;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, l; cin >> n >> l;
	vector<point> a(n + n);
	for(int i = 0; i < n; i++){
		int x, y; cin >> x >> y;
		a[i] = a[i + n] = point(x, y);
	}
	vector<llf> dsum(n + n);
	for(int i = 0; i < n + n - 1; i++){
		dsum[i + 1] = dsum[i] + abs(a[i + 1] - a[i]);
	}
	llf ret = 0;
	auto candoit = [&](int i, int j){
		point A = a[i + 1] - a[i];
		point B = a[j] - a[j - 1];
		if(ccw(A, B) <= eps && i + 1 != j) return false;
		llf min_dist = 0;
		if(i + 1 == j) min_dist = dsum[n];
		else{
			point p = insec(a[i], a[i + 1], a[j - 1], a[j]);
			min_dist = dsum[n] - (dsum[j] - dsum[i]) + abs(a[i] - p) + abs(a[j] - p);
		}
		if(min_dist > l) return false;
		llf max_dist = 1e18;	
		point C = a[i] - a[i + n - 1];
		point D = a[j + 1] - a[j];
		if(ccw(C, D) > eps){
			point p = insec(a[i + n - 1], a[i], a[j], a[j + 1]);
			max_dist = dsum[n] - (dsum[j] - dsum[i]) + abs(a[i] - p) + abs(a[j] - p);
		}
		if(max_dist < l) return false;
		return true;
	};
	int j = 1;
	for(int i = 0; i < n; i++){
		while(!candoit(i, j)) j++;
		while(j < i + n && candoit(i, j)){
			point vecX = (a[i] - a[j]);
			llf xarg = arg(vecX);
			point center = (a[i] + a[j])  * (llf)0.5;
			llf major = l - (dsum[n] - (dsum[j] - dsum[i]));
			llf minor = sqrt(major * major - abs(vecX) * abs(vecX));
			major /= 2;
			minor /= 2;
			auto toCircle = [&](point p){
				p -= center;
				p *= exp(point(0, -xarg));
				return point(p.real() / major, p.imag() / minor);
			};
			auto restore = [&](point p){
				p = point(major * p.real(), minor * p.imag());
				p *= exp(point(0, xarg));
				return p + center;
			};
			auto fn = [&](point p, point q){
				return (p.imag() + q.imag()) * (q.real() - p.real());
			};
			point S1 = circleLine(toCircle(a[i + n - 1]), toCircle(a[i]));
			point E1 = circleLine(toCircle(a[i]), toCircle(a[i + 1]));
			point S2 = circleLine(toCircle(a[j]), toCircle(a[j - 1]));
			point E2 = circleLine(toCircle(a[j + 1]), toCircle(a[j]));
			point S = (ccw(S1, S2) > 0 ? S2 : S1);
			point E = (ccw(E1, E2) > 0 ? E1 : E2);
			//		cout << setprecision(69) << arg(S) << " " << arg(E) << "\n";
			ret += major * minor * fmod(arg(E) - arg(S) + 1e-13, 2 * acos(-1)) + fn(restore(E), center) + fn(center, restore(S));
			j++;
		}
		j--;
	}
	cout << setprecision(69) << ret / 2 << endl;
}
