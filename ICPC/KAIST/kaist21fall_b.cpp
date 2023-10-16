#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 993244853;
const int MAXN = 605;

struct mint {
    int val;
    mint() { val = 0; }
    mint(const lint& v) {
        val = (-mod <= v && v < mod) ? v : v % mod;
        if (val < 0) val += mod;
    }

    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.val; }
    friend bool operator==(const mint& a, const mint& b) { return a.val == b.val; }
    friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
    friend bool operator<(const mint& a, const mint& b) { return a.val < b.val; }

    mint operator-() const { return mint(-val); }
    mint& operator+=(const mint& m) { if ((val += m.val) >= mod) val -= mod; return *this; }
    mint& operator-=(const mint& m) { if ((val -= m.val) < 0) val += mod; return *this; }
    mint& operator*=(const mint& m) { val = (lint)val*m.val%mod; return *this; }
    friend mint ipow(mint a, lint p) {
        mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a;
        return ans;
    }
    friend mint inv(const mint& a) { assert(a.val); return ipow(a, mod - 2); }
    mint& operator/=(const mint& m) { return (*this) *= inv(m); }

    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    operator int64_t() const {return val; }
};


template<typename T>
struct poly {
	T a[2];

    poly(){ a[0] = a[1] = T(0); }
    poly(T a0){ a[0] = a0, a[1] = T(0); }
    poly(T a0, T a1){ a[0] = a0, a[1] = a1; }
    poly(T* b){ a[0] = b[0], a[1] = b[1]; }


    T operator [](int idx) const {
    	return a[idx];
    }

    T& coef(size_t idx) { // mutable reference at coefficient
        return a[idx];
    }

    bool isZero(){
    	for(int i = 0; i < 2; i++) if(a[i] != T(0)) return 0;
    	return 1;
	}

    poly trim(size_t idx){
    	poly ret;
    	for(int i = 0; i < 2; i++){
    		if(i < idx) ret.a[i] = a[i];
    		else ret.a[i] = T(0);
		}
		return ret;
	}
    poly operator *= (const T &x) {
    	for(int i = 0; i < 2; i++){
    		a[i] *= x;
        }
        return *this;
    }
    poly operator /= (const T &x) {
        return *this *= (T(1)/ T(x));
    }
    poly operator * (const T &x) const {return poly(*this) *= x;}
    poly operator / (const T &x) const {return poly(*this) /= x;}

    poly operator+=(const poly &p){
        for(int i=0; i<2; i++){
            a[i] += p.a[i];
        }
        return *this;
    }
    poly operator-=(const poly &p){
        for(int i=0; i<2; i++){
            a[i] -= p.a[i];
        }
        return *this;
    }
    poly operator*=(const poly &p){
    	mint a0 = a[0] * p.a[0];
    	mint a1 = mint((lint)a[1].val * p.a[0].val + (lint)a[0].val * p.a[1].val);
    	a[0] = a0;
    	a[1] = a1;
        return *this;
    }
    poly inv(){
    	assert(a[0] != T(0));
    	mint val = T(1) / (a[0] * a[0]);
    	return poly(a[0] * val, -a[1] * val);
    }

    poly operator+(const poly &p)const{ return poly(*this) += p; }
    poly operator-(const poly &p)const{ return poly(*this) -= p; }
    poly operator*(const poly &p)const{ return poly(*this) *= p; }
};

using pol = poly<mint>;
using matrix = vector<vector<pol>>;

mt19937 rng(0x14004);
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

struct jaryoguzo{
	pol m[MAXN][2 * MAXN];
	int getRow(int R, int i, int nex) {
		for(int j = nex; j < R; j++){
			if (!m[j][i].isZero()) return j;
		}
		return -1;
	}

	pair<pol,int> gauss(int n){
		int R = n, C = 2 * n, rank = 0, nex = 0;
		pol prod = pol(1);
		for(int i = 0; i < C; i++){
			int row = getRow(R,i,nex);
			if (row == -1) {  continue; }
			if (row != nex) prod *= mint(-1), swap(m[row],m[nex]);
			prod *= m[nex][i]; rank ++;
			pol x = m[nex][i].inv();
			for(int k = i; k < C; k++) m[nex][k] *= x;
			for(int j = 0; j < R; j++) if (j != nex) {
				pol v = m[j][i]; if (v.isZero()) continue;
				for(int k = i; k < C; k++) m[j][k] -= v*m[nex][k];
			}
			nex ++;
		}
		return {prod,rank};
	}

	int n;
	
	pol adjoint(matrix mm) {
		int R = sz(mm);
		for(int i = 0; i < R; i++){
			m[i][i+R] = pol(1);
			for(int j = 0; j < R; j++){
				m[i][j] = mm[i][j];
			}
		}
		pair<pol, int> gv = gauss(R);
		if(gv.second != R) assert(0);
		return gv.first;
	}

	pol det;

	void init(matrix a){
		det = adjoint(a);
		n = sz(a);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				m[i][j] = a[i][j];
			}
		}
	}

	pol query(int x, int y){
		return m[x][n+y] * det;
	}

	void update(int x, int y, pol z){

		// Apply Sherman-Morrisson.
		pol c = z - m[x][y];

		// minusCoeff = 1/(1 + v^T A^-1 u)
		pol minusCoeff = c * m[y][n+x] + pol(1);
		det *= minusCoeff;
		minusCoeff = minusCoeff.inv();
		minusCoeff *= c;

		// toAdd = (A^-1 * u) * (v^T * A^-1)
		static vector<pol> r1, r2;
		r1.resize(n);
		r2.resize(n);
		for(int i = 0; i < n; i++){
		    r1[i] = m[i][n+x] * minusCoeff;
		    r2[i] = m[y][n+i];
		}
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				m[i][j+n] -= r1[i] * r2[j];
			}
		}

		m[x][y] = c;
	}

}ds;

int main(){
	int n, q;
	scanf("%d %d",&n,&q);
	vector<vector<int>> adj(n, vector<int>(n));
	vector<vector<mint>> rnd(n, vector<mint>(n));
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			scanf("%d",&adj[i][j]);
			if(i != j) rnd[i][j] = randint(1, mod - 1);
			else rnd[i][j] = 1;
		}
	}
	auto newPoly = [&](mint v, int deg){
		return pol(deg == 0 ? v : mint(0), deg == 1 ? v : mint(0));
	};
	matrix a = matrix(n, vector<pol>(n));
	for(int j = 0; j < n; j++){
		for(int k = 0; k < n; k++){
			a[j][k] = newPoly(rnd[j][k], adj[j][k]);
		}
	}
	ds.init(a);
	for(int i = 0; i < q; i++){
		int t, x, y;
		scanf("%d %d %d",&t,&x,&y);
		x--; y--;
		if(t == 1){
			auto ret = ds.query(x, y);
			int ptr = 0;
			while(ptr < 2 && ret[ptr] == mint(0)) ptr++;
			printf("%d\n", ptr);
		}
		else{
			int c; scanf("%d",&c);
			ds.update(x, y, newPoly(rnd[x][y], c));
			adj[x][y] = c;
		}
	}
}


