#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;

struct edg{
	int s, e;
	int a, b, c; // axx + bx + c
};

struct edg2{
	int idx;
	int s, e;
	double dis;
	bool operator<(const edg2 &a)const{
		return dis < a.dis;
	};
};

struct event{
	int s, e;
	double x;
	bool operator<(const event &ev)const{
		return x < ev.x;
	}
};

struct disj{
	int pa[1005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n;
int x[55], y[55], z[55], vx[55], vy[55], vz[55];
int chk[1300];

void solve(double t){
	memset(chk, 0, sizeof(chk));
	vector<edg2> v;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			double dx = x[i] - x[j] + (vx[i] - vx[j]) * t;
			double dy = y[i] - y[j] + (vy[i] - vy[j]) * t;
			double dz = z[i] - z[j] + (vz[i] - vz[j]) * t;
			v.push_back({(int)v.size(), i, j, dx * dx + dy * dy + dz * dz});
		}
	}
	sort(v.begin(), v.end());
	disj.init(n);
	for(auto &i : v){
		chk[i.idx] = disj.uni(i.s, i.e);
	//	if(chk[i.idx]) printf("%d %d\n", i.s, i.e);
	}
}

vector<double> quad(int a, int b, int c){
	if(a == 0 && b == 0) return vector<double>();
	if(a == 0){
		vector<double> v = {-1.0 * c / b};
		return v;
	}
	if(1ll * b * b - 4ll * a * c < 0) return vector<double>();
	if(1ll * b * b - 4ll * a * c == 0){
		vector<double> v = {-0.5 * b / a};
		return v;
	}
	double d1 = -0.5 * b / a;
	double d2 = sqrt(1ll * b * b - 4ll * a * c) / (2 * a);
	d2 = fabs(d2);
	vector <double> v = {d1-d2, d1+d2};
	return v;
}

int main(){
	int tc = 0;
	while(~scanf("%d",&n)){
		for(int i=0; i<n; i++){
			cin >> x[i] >> y[i] >> z[i] >> vx[i] >> vy[i] >> vz[i];
		}
		vector<edg> seg;
		for(int i=0; i<n; i++){
			for(int j=0; j<i; j++){
				int b = x[i] - x[j];
				int d = y[i] - y[j];
				int f = z[i] - z[j];
				int a = vx[i] - vx[j];
				int c = vy[i] - vy[j];
				int e = vz[i] - vz[j];
				seg.push_back({j, i, a*a+c*c+e*e, 2*a*b+2*c*d+2*e*f, b*b+d*d+f*f});
			}
		}
		vector<event> vt;
		for(int i=0; i<seg.size(); i++){
			for(int j=0; j<i; j++){
				if(make_tuple(seg[i].a, seg[i].b, seg[i].c) == make_tuple(seg[j].a, seg[j].b, seg[j].c)) continue;
				vector<double> v = quad(seg[i].a - seg[j].a, seg[i].b - seg[j].b, seg[i].c - seg[j].c);
			//	printf("cross of %d %d %d %d ", seg[i].s, seg[i].e, seg[j].s, seg[j].e);
			//	for(auto &k : v) printf("%.10f ", k);
			//	puts("");
				int st = i, ed = j; // i is smaller in inf
				if(make_tuple(seg[i].a, seg[i].b, seg[i].c) > make_tuple(seg[j].a, seg[j].b, seg[j].c)){
					swap(st, ed);
				}
				reverse(v.begin(), v.end()); // rev time order
				while(!v.empty() && v.back() < 0) v.pop_back();
				for(int k=0; k<v.size(); k++){
					vt.push_back({ed, st, v[k]});
					swap(ed, st);
				}
			}
		}
		sort(vt.begin(), vt.end());
	//	for(auto &i : vt) printf("%d %d %.10f\n", i.s, i.e, i.x);
		solve(0);
		int ans = 0;
		for(int i=0; i<vt.size(); ){
			int e = i;
			while(e < vt.size() && vt[e].x - vt[i].x < 1e-7) e++;
			bool ok = 0;
			for(int j=i; j<e; j++){
				if(chk[vt[j].s]) ok = 1;
			}
			if(!ok){
				i = e;
				continue;
			}
			vector<int> vl;
			for(int j=0; j<seg.size(); j++) vl.push_back(chk[j]);
	//		printf("%.10f\n", vt[i].x + 1e-7);
			solve(vt[i].x + 1e-7);
			for(int j=0; j<seg.size(); j++){
				if(vl[j] != chk[j]){
		//			printf("ok\n", vt[i].x);
					ans++;
					break;
				}
			}
			i = e;
		}
		printf("Case %d: %d\n", ++tc, ans + 1);
	}
}
