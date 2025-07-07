// Gemini 2.5 Pro
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

// Define a constant for Pi for trigonometric calculations
const long double PI = acos(-1.0L);

// Use std::complex to represent a point or a vector in 2D space
using Point = complex<long double>;

// Calculates the squared Euclidean distance between two points.
// norm(p2 - p1) calculates the squared magnitude of the vector between the points.
long double distSq(Point p1, Point p2) { return norm(p2 - p1); }

// Calculates the Euclidean distance between two points.
// abs(p2 - p1) calculates the magnitude of the vector between the points.
long double dist(Point p1, Point p2) { return abs(p2 - p1); }

// The core logic to solve a single test case
void solve() {
	long double ax, ay, bx, by, cx, cy, r;
	cin >> ax >> ay >> bx >> by >> cx >> cy >> r;

	Point a(ax, ay);
	Point b(bx, by);
	Point c(cx, cy);

	// Calculate squared distances of Alice and Bob from the circle's center
	long double dist_a_c_sq = distSq(a, c);
	long double dist_b_c_sq = distSq(b, c);
	long double r_sq = r * r;

	// --- Case 1: The straight path from A to B is the shortest ---

	// Check if either Alice or Bob is inside or on the circle.
	if (dist_a_c_sq <= r_sq || dist_b_c_sq <= r_sq) {
		cout << fixed << setprecision(15) << dist(a, b) << "\n";
		return;
	}

	// Check if the line segment AB intersects the circle.
	Point vec_ab = b - a;
	Point vec_ac = c - a;

	// Dot product of two vectors represented by complex numbers z1, z2 is real(conj(z1) * z2)
	long double dot_product = (conj(vec_ab) * vec_ac).real();
	long double len_ab_sq = norm(vec_ab);

	long double t = -1.0;
	if (len_ab_sq > 1e-9) { // Avoid division by zero if A and B are the same point
		t = dot_product / len_ab_sq;
	}

	long double dist_c_line_sq;
	if (t >= 0 && t <= 1) {
		// Projection is on the segment AB. Find distance from C to the line.
		Point projection = a + t * vec_ab;
		dist_c_line_sq = distSq(c, projection);
	} else {
		// Projection is outside the segment. Set distance to a large value.
		dist_c_line_sq = 1e18;
	}

	if (dist_c_line_sq <= r_sq) {
		cout << fixed << setprecision(15) << dist(a, b) << "\n";
		return;
	}

	// --- Case 2: Both are outside and the direct path misses the circle ---
	// The optimal point P lies on the circle. We find it with ternary search.
	// The search space is the shorter arc on the circle between the lines CA and CB.

	Point vec_ca = a - c;
	Point vec_cb = b - c;
	long double angle_a = atan2(vec_ca.imag(), vec_ca.real());
	long double angle_b = atan2(vec_cb.imag(), vec_cb.real());

	long double low, high;

	// Determine the shorter arc for the search range.
	if (abs(angle_a - angle_b) < PI) {
		low = min(angle_a, angle_b);
		high = max(angle_a, angle_b);
	} else {
		// The shorter arc crosses the -PI/PI boundary
		if (angle_a < angle_b) {
			low = angle_b;
			high = angle_a + 2 * PI;
		} else {
			low = angle_a;
			high = angle_b + 2 * PI;
		}
	}

	auto path_length = [&](long double angle) {
		// A point on a circle can be represented as center + radius * e^(i*angle)
		Point p = c + polar(r, angle);
		return dist(a, p) + dist(b, p);
	};

	// Run ternary search for a fixed number of iterations (100 is sufficient for high precision).
	for (int i = 0; i < 100; ++i) {
		long double m1 = low + (high - low) / 3.0;
		long double m2 = high - (high - low) / 3.0;
		if (path_length(m1) < path_length(m2)) {
			high = m2;
		} else {
			low = m1;
		}
	}

	cout << fixed << setprecision(15) << path_length(low) << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}