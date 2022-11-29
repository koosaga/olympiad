namespace Euclid{
	lint gcd(lint x, lint y) { return y ? gcd(y, x%y) : x; }
	lint mod(lint a, lint b) { return ((a%b) + b) % b; }

	// returns g = gcd(a, b); finds x, y such that g = ax + by
	lint ext_gcd(lint a, lint b, lint &x, lint &y) {
		lint xx = y = 0;
		lint yy = x = 1;
		while (b) {
			lint q = a / b;
			lint t = b; b = a%b; a = t;
			t = xx; xx = x - q*xx; x = t;
			t = yy; yy = y - q*yy; y = t;
		}
		return a;
	}

	// computes b such that ab = 1 (mod n), returns -1 on failure
	lint mod_inverse(lint a, lint n) {
		lint x, y;
		lint g = ext_gcd(a, n, x, y);
		if (g > 1) return -1;
		return mod(x, n);
	}

	// Chinese remainder theorem: find z such that
	// z % m1 = r1, z % m2 = r2.  Here, z is unique modulo M = lcm(m1, m2).
	// Return (z, M).  On failure, M = -1.
	pair<lint, lint> CRT(lint m1, lint r1, lint m2, lint r2) {
		lint s, t;
		lint g = ext_gcd(m1, m2, s, t);
		if (r1%g != r2%g) return make_pair(0, -1);
		s = mod(s * r2, m2);
		t = mod(t * r1, m1);
		return make_pair(mod(s*(m1/g) + t*(m2/g), m1*(m2/g)), m1*(m2/g));
	}
}

// fraction finder
// https://codeforces.com/blog/entry/50244?#comment-341659
#define x first
#define y second
pair<long long, long long> solve(pair<int, int> L, pair<int, int> R){
//	printf("%.10Lf %.10Lf\n", L, R);
    pair<long long, long long> l(0, 1), r(1, 0);
    for(;;){
        pair<long long, long long> m(l.x+r.x, l.y+r.y);
        fflush(stdout);
        if(L.first*m.x<=L.second*m.y){// move to the right;
            long long kl=1, kr=1;
            while(L.first*(l.x+kr*r.x) <= L.second*(l.y+kr*r.y))kr*=2;// exponential search
            while(kl!=kr){
                long long km = (kl+kr)/2;
                if(L.first*(l.x+km*r.x) <= L.second*(l.y+km*r.y)) kl=km+1;
                else kr=km;
            }
            l = make_pair(l.x+(kl-1)*r.x, l.y+(kl-1)*r.y);
        } else if(R.first*m.x>=R.second*m.y){//move to the left
            long long kl=1, kr=1;
            while(R.first*(r.x+kr*l.x)>=R.second*(r.y+kr*l.y))kr*=2;// exponential search
            while(kl!=kr){
                long long km = (kl+kr)/2;
                if(R.first*(r.x+km*l.x)>=R.second*(r.y+km*l.y)) kl = km+1;
                else kr = km;
            }
            r = make_pair(r.x+(kl-1)*l.x, r.y+(kl-1)*l.y);
        } else {
            return m;
        }
    }
}


// x < ans < y, all argument should be nonnegative, x != pi(0, 0), y != pi(0, 0). 
// minimize y, in case of tie x.

pi minY(pi x, pi y){ 
	auto fuck =  solve(x, y);
	return pi(fuck.second, fuck.first);
}


// number of (x, y) : (0 <= x < n && 0 < y <= k/d x + b/d)
// argument should be positive
ll count_solve(ll n, ll k, ll b, ll d) {
	if (k == 0) {
		return (b / d) * n;
	}
	if (k >= d || b >= d) {
		return ((k / d) * (n - 1) + 2 * (b / d)) * n / 2 + count_solve(n, k % d, b % d, d);
	}
	return count_solve((k * n + b) / d, d, (k * n + b) % d, k);
}


// Given argument (n, m, a, b), find min((ax + b) mod m) for 0 <= x < n
// Assumes no multiplication overflow. O(log m)
// Ref: https://judge.yosupo.jp/submission/102303
template <typename T> T linear_mod_min(T n, const T &m, T a, T b, bool is_min = true, T p = 1, T q = 1) {
	if (a == 0)
		return b;
	if (is_min) {
		if (b >= a) {
			T t = (m - b + a - 1) / a;
			T c = (t - 1) * p + q;
			if (n <= c)
				return b;
			n -= c;
			b += a * t - m;
		}
		b = a - 1 - b;
	} else {
		if (b < m - a) {
			T t = (m - b - 1) / a;
			T c = t * p;
			if (n <= c)
				return a * ((n - 1) / p) + b;
			n -= c;
			b += a * t;
		}
		b = m - 1 - b;
	}
	T d = m / a;
	T c = linear_mod_min(n, a, m % a, b, !is_min, (d - 1) * p + q, d * p + q);
	return is_min ? a - 1 - c : m - 1 - c;
}

