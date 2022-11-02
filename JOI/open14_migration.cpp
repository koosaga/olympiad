#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 2005;

// Change terminating condition appropriately.
// For test 1, 2, 4, terminates in several minutes.
// For test 3, 5, terminates in 48 hours.
// DLAS is written by cgiosy: https://gist.github.com/cgiosy/ed16f4988eeb7e989a97644fe61e1561

namespace dlas{
	using u64 = uint64_t;

	template<class T, class U>
		T incMod(T x, U mod) {
			x += 1;
			return x == mod ? 0 : x;
		}

	template<class Domain, class CoDomain, size_t LEN = 5>
		std::pair<Domain, CoDomain> dlas(
				std::function<CoDomain(Domain&)> f,
				std::function<void(Domain&)> mutate,
				Domain const& initial,
				u64 maxIdleIters = -1ULL
				) {
			std::array<Domain, 3> S{initial, initial, initial};
			CoDomain curF = f(S[0]);
			size_t curPos = 0;
			size_t minPos = 0;

			std::array<CoDomain, LEN> fitness;
			std::fill(fitness.begin(), fitness.end(), curF);
			CoDomain minF = curF;
			size_t k = 0;

			for (u64 idleIters = 0; idleIters < maxIdleIters; idleIters += 1) {
				CoDomain prvF = curF;

				size_t newPos = incMod(curPos, 3);
				if (newPos == minPos) newPos = incMod(newPos, 3);

				Domain& curS = S[curPos];
				Domain& newS = S[newPos];

				newS = curS;
				mutate(newS);
				CoDomain newF = f(newS);
				if (newF < minF) {
					idleIters = 0;
					minPos = newPos;
					minF = newF;
				}
				if (newF == curF || newF < *std::max_element(fitness.begin(), fitness.end())) {
					curPos = newPos;
					curF = newF;
				}

				CoDomain& fit = fitness[k];
				if (curF > fit || curF < fit && curF < prvF) {
					fit = curF;
				}
				k = incMod(k, LEN);
			}
			return { S[minPos], minF };
		}
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }
int tot = 10000;
vector<pi> gph, coords;

struct state{
	template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
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
};
	template<class P>
bool segmentIntersectionQ(P s1, P e1, P s2, P e2) {
	if (e1 == s1) {
		if (e2 == s2) return e1 == e2;
		swap(s1,s2); swap(e1,e2);
	}
	P v1 = e1-s1, v2 = e2-s2, d = s2-s1;
	auto a = v1.cross(v2), a1 = d.cross(v1), a2 = d.cross(v2);
	if (a == 0) { // parallel
		auto b1 = s1.dot(v1), c1 = e1.dot(v1),
		     b2 = s2.dot(v1), c2 = e2.dot(v1);
		return !a1 && max(b1,min(b2,c2)) <= min(c1,max(b2,c2));
	}
	if (a < 0) { a = -a; a1 = -a1; a2 = -a2; }
	return (0 <= a1 && a1 <= a && 0 <= a2 && a2 <= a);
}

vector<int> f;
	int score(){
		int ans = 0;
		for(int i = 0; i < sz(gph); i++){
			for(int j = 0; j < i; j++){
				Point<lint> a(coords[f[gph[i].first]].first, coords[f[gph[i].first]].second);
				Point<lint> b(coords[f[gph[i].second]].first, coords[f[gph[i].second]].second);
				Point<lint> c(coords[f[gph[j].first]].first, coords[f[gph[j].first]].second);
				Point<lint> d(coords[f[gph[j].second]].first, coords[f[gph[j].second]].second);
				if(a == c || a == d || b == c || b == d) continue;
				if(segmentIntersectionQ(a, b, c, d)) ans++;
			}
		}
		if(tot > ans){
			tot = ans;
			cerr << "update" << ans << endl;
			if(ans <= 72000){
				cerr << "fuck yeah" << endl;
				for(auto &x : f) cout << x + 1 << "\n";
				exit(0);
			}
		}
		return ans;
	}
	void mutate(){
		if(randint(0, 1) < 1){
			bool chk[500] = {};
			int z = randint(0, sz(f) - 1);
			for(auto &x : f) chk[x] = 1;
			chk[f[z]] = 0;
			vector<int> v;
			for(int i = 0; i < sz(coords); i++){
				if(!chk[i]) v.push_back(i);
			}
			f[z] = v[randint(0, sz(v) - 1)];
		}
		else{
			int p = randint(0, sz(f) - 1);
			int q = randint(0, sz(f) - 1);
			swap(f[p], f[q]);
		}
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	state ret;
	int n, m;
	cin >> n >> m;
	gph.resize(m);
	for(auto &[x, y] : gph) cin >> x >> y, x--, y--;
	int l; cin >> l;
	coords.resize(l);
	for(auto &[x, y] : coords) cin >> x >> y;
	auto sc = [](state b){ return b.score(); };
	auto mut = [](state &b){ b.mutate(); };
	int cur = 0;
	while(1){
		tot = 1e9;
		state init;
		init.f.resize(l);
		iota(all(init.f), 0);
		shuffle(all(init.f), rng);
		init.f.resize(n);
		// For test 3, 5 we can't run it several times, but the solution does not converge. Otherwise it's better to run only 100k~1m iterations and retry.
		auto [board, ans] = dlas::dlas<state, int>(sc, mut, init);
		if(ans > cur){
			cur = ans;
			ret = board;
		}
		cerr << "Reinit" << endl;
	}
}
