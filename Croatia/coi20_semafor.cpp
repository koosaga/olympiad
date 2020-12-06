// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int N = 100;
const int mod = 1e9 + 7;


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

const int msk[10] = {
	0+2+0+8+0,
	0+2+0+0+0,
	1+0+0+8+0,
	1+2+4+0+0,
	0+2+0+0+16,
	1+0+4+0+16,
	0+0+4+8+0,
	1+2+0+0+0,
	1+0+4+8+16,
	1+2+4+0+16};

struct mtrx{
	mint a[N][N];
	mtrx(){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				a[i][j] = mint(0);
			}
		}
	}
	mtrx(int x){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				a[i][j] = mint(i == j ? x : 0);
			}
		}
	}
	mtrx operator*(const mtrx &m)const{
		mtrx ret;
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				for(int k=0; k<N; k++){
					ret.a[j][k] += a[j][i] * m.a[i][k];
				}
			}
		}
		return ret;
	}
};

mtrx pwr(mtrx A, lint k){
	if(k == 0) return mtrx(1);
	if(k & 1) return A * pwr(A * A, k / 2);
	return pwr(A * A, k / 2);
}

mint bino[20][20];

mtrx trans(lint num, int n){
	mtrx m;
	for(int i=0; i<=n; i++){
		if(i > 0) m.a[i][i-1] = mint(i);
		if(i < n) m.a[i][i+1] = mint(n-i);
	}
	auto foo = pwr(m, num);
	return foo;
}

int main(){
	for(int i=0; i<20; i++){
		bino[i][0] = mint(1);
		for(int j=1; j<=i; j++) bino[i][j] = bino[i-1][j-1] + bino[i-1][j];
	}
	lint m, n, k, x;
	cin >> m >> n >> k >> x;
	mtrx AA = trans(k, 5 * m);
	mtrx BB = trans(n % k, 5 * m);
	if(m == 1){
		mtrx A, B;
		for(int i = 0; i < 10; i++){
			for(int j = 0; j < 10; j++){
				int qq = __builtin_popcount(msk[i] ^ msk[j]);
				A.a[i][j] = AA.a[0][qq] / bino[5][qq];
				B.a[i][j] = BB.a[0][qq] / bino[5][qq];
			}
		}
		A = pwr(A, n / k) * B;
		for(int i=0; i<10; i++) cout << A.a[x][i] << endl;
		return 0;
	}
	if(m == 2){
		mtrx A, B;
		for(int i = 0; i < 100; i++){
			for(int j = 0; j < 100; j++){
				int qq =
				__builtin_popcount(msk[i / 10] ^ msk[j / 10]) + 
				__builtin_popcount(msk[i % 10] ^ msk[j % 10]);
				A.a[i][j] = AA.a[0][qq] / bino[10][qq];
				B.a[i][j] = BB.a[0][qq] / bino[10][qq];
			}
		}
		A = pwr(A, n / k) * B;
		for(int i=0; i<100; i++) cout << A.a[x][i] << endl;
		return 0;
	}
}
