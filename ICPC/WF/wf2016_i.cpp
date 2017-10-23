#include<bits/stdc++.h>
using namespace std;

//Simplex Algorithm: Ax <= b, Maximize c^T x 
//-INF not feasible; INF when unbounded
//accuracy ~ (size of ans) * EPS
//EPS recommended 1e-9 on double, 1e-12 on long double
//expected n ~ 100, 10ms. worst case is exponential
//Usage: Simplex(VVD A, VD b, VD c).solve(VD ans);

using real_t = double;
using ld = double;
using VD = vector<real_t>;
using VVD = vector<VD>;
const real_t EPS = 1e-9;

struct Simplex{
	int m, n;
	vector<int> B, N;
	VVD D;
	Simplex(const VVD& A, const VD& b, const VD &c)
		: m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, VD(n+2)){
			for(int i=0; i<m; ++i) for(int j=0; j<n; ++j) D[i][j] = A[i][j];
			for(int i=0; i<m; ++i) B[i] = n+i, D[i][n] = -1, D[i][n+1] = b[i];
			for(int j=0; j<n; ++j) N[j] = j, D[m][j] = -c[j];
			N[n] = -1; D[m+1][n] = 1;
		}
	void Pivot(int r, int s) {
		real_t inv = 1/D[r][s];
		for(int i=0; i<m+2; ++i){
			for(int j=0; j<n+2; ++j){
				if(i != r && j != s) D[i][j] -= D[r][j] * D[i][s] * inv;
			}
		}
		for(int i=0; i<m+2; ++i) if(i != r) D[i][s] *= -inv;
		for(int j=0; j<n+2; ++j) if(j != s) D[r][j] *= inv;
		D[r][s] = inv; swap(B[r], N[s]);
	}
	   bool Phase(bool p) {
	   int x = m + p;
	   while(true) {
			int s = -1;
			for(int j=0; j<=n; ++j){
				if(!p && N[j] == -1) continue;
				if(s == -1 || D[x][j] < D[x][s]) s = j;
			}
			if(D[x][s] > -EPS) return true;
			int r = -1;
			for(int i=0; i<m; ++i){
				if(D[i][s] <= EPS) continue;
				if(r == -1 || D[i][n+1] / D[i][s] < D[r][n+1] / D[r][s]) r = i;
			}
			if(r == -1) return false;
			Pivot(r, s);
		}
	}
	real_t solve(VD &x) {
		int r = 0;
		for(int i=1; i<m; ++i) if(D[i][n+1] < D[r][n+1]) r=i;
		if(D[r][n+1] < -EPS) {
			Pivot(r, n);
			if(!Phase(1) || D[m+1][n+1] < -EPS) return -1/0.0;
			for(int i=0; i<m; ++i) if(B[i] == -1) {
				int s = min_element(D[i].begin(), D[i].end() - 1) - D[i].begin();
				Pivot(i, s);
			}
		}
		if(!Phase(0)) return 1/0.0;
		x = VD(n);
		for(int i=0; i<m; ++i) if(B[i] < n) x[B[i]] = D[i][n+1];
		return D[m][n+1];
	}
};

int n, m, a[33][33];
int adj[33][33], trk[33][33];
int idx[33][33];

vector<int> spath(int s, int e){
	if(trk[s][e] == -1){
		vector<int> ret = {idx[s][e]};
		return ret;
	}
	auto l = spath(s, trk[s][e]);
	auto r = spath(trk[s][e], e);
	for(auto &i : r) l.push_back(i);
	return l;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> a[i][j];
			if(a[i][j] > 0){
				idx[i][j] = m++;
				adj[i][j] = a[i][j];
			}
			else{
				idx[i][j] = -1;
				adj[i][j] = 1e9;
			}
		}
	}
	memset(trk, -1, sizeof(trk));
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if(adj[j][k] > adj[j][i] + adj[i][k]){
					adj[j][k] = adj[j][i] + adj[i][k];
					trk[j][k] = i;
				}
			}
		}
	}
	vector<vector<real_t>> A;
	vector<real_t> B;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(idx[i][j] != -1){
				vector<real_t> p1(m);
				p1[idx[i][j]] = -1;
				A.push_back(p1);
				B.push_back(-a[i][j]);
				p1[idx[i][j]] = 1;
				A.push_back(p1);
				B.push_back(2 * a[i][j]);
			}
		}
	}
	int q; cin >> q;
	while(q--){
		int s, e, x;
		cin >> s >> e >> x;
		if(s == e) continue;
		auto l = spath(s, e);
		vector<real_t> p1(m);
		for(auto &i : l) p1[i] = 1;
		A.push_back(p1);
		B.push_back(x);
		for(auto &i : l) p1[i] = -1;
		A.push_back(p1);
		B.push_back(-x);
	}
	vector<real_t> aux;
	cin >> q;
	while(q--){
		int s, e;
		cin >> s >> e;
		if(s == e){
			printf("%d %d 0 0\n", s, e);
			continue;
		}
		auto l = spath(s, e);
		printf("%d %d ", s, e);
		vector<real_t> x(m);
		for(auto &i : l) x[i] = -1;
		printf("%.10f ", -Simplex(A, B, x).solve(aux));
		for(auto &i : l) x[i] = 1;
		printf("%.10f\n", Simplex(A, B, x).solve(aux));
	}
}
