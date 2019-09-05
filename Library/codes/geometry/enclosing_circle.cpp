namespace cover_2d{
	double eps = 1e-9;
	using Point = complex<double>;
	struct Circle{ Point p; double r; };
	double dist(Point p, Point q){ return abs(p-q); }
	double area2(Point p, Point q){ return (conj(p)*q).imag(); }
	bool in(const Circle& c, Point p){ return dist(c.p, p) < c.r + eps; }
	Circle INVAL = Circle{Point(0, 0), -1};
	Circle mCC(Point a, Point b, Point c){
		b -= a; c -= a;
		double d = 2*(conj(b)*c).imag(); if(abs(d)<eps) return INVAL;
		Point ans = (c*norm(b) - b*norm(c)) * Point(0, -1) / d;
		return Circle{a + ans, abs(ans)};
	}
	Circle solve(vector<Point> p) {
		mt19937 gen(0x94949); shuffle(p.begin(), p.end(), gen);
		Circle c = INVAL;
		for(int i=0; i<p.size(); ++i) if(c.r<0 ||!in(c, p[i])){
			c = Circle{p[i], 0};
			for(int j=0; j<=i; ++j) if(!in(c, p[j])){
				Circle ans{(p[i]+p[j])*0.5, dist(p[i], p[j])*0.5};
				if(c.r == 0) { c = ans; continue; }
				Circle l, r; l = r = INVAL;
				Point pq = p[j]-p[i];
				for(int k=0; k<=j; ++k) if(!in(ans, p[k])) {
					double a2 = area2(pq, p[k]-p[i]);
					Circle c = mCC(p[i], p[j], p[k]);
					if(c.r<0) continue;
					else if(a2 > 0 && (l.r<0||area2(pq, c.p-p[i]) > area2(pq, l.p-p[i]))) l = c;
					else if(a2 < 0 && (r.r<0||area2(pq, c.p-p[i]) < area2(pq, r.p-p[i]))) r = c;
				}
				if(l.r<0&&r.r<0) c = ans;
				else if(l.r<0) c = r;
				else if(r.r<0) c = l;
				else c = l.r<=r.r?l:r;
			}
		}
		return c;
	}
};

namespace cover_3d{
	double enclosing_sphere(vector<double> x, vector<double> y, vector<double> z){
		int n = x.size();
		auto hyp = [](double x, double y, double z){
			return x * x + y * y + z * z;
		};
		double px = 0, py = 0, pz = 0;
		for(int i=0; i<n; i++){
			px += x[i];
			py += y[i];
			pz += z[i];
		}
		px *= 1.0 / n;
		py *= 1.0 / n;
		pz *= 1.0 / n;
		double rat = 0.1, maxv;
		for(int i=0; i<10000; i++){
			maxv = -1;
			int maxp = -1;
			for(int j=0; j<n; j++){
				double tmp = hyp(x[j] - px, y[j] - py, z[j] - pz);
				if(maxv < tmp){
					maxv = tmp;
					maxp = j;
				}
			}
			px += (x[maxp] - px) * rat;
			py += (y[maxp] - py) * rat;
			pz += (z[maxp] - pz) * rat;
			rat *= 0.998;
		}
		return sqrt(maxv);
	}
};
