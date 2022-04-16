#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 805;
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

mint D[MAXN][MAXN], E[MAXN][MAXN];
mint DS[MAXN], DS2[MAXN][MAXN];
mint ES[MAXN][MAXN], ES2[MAXN][MAXN];
int pnxt[MAXN][MAXN];

int count(std::vector<int> P){
	int N = sz(P);
	vector<int> A(N);
	vector<int> nxt(N);
	for(int j = 0; j < N; j++){
		A[j] = (abs(P[j]) - 1) * 2 + (P[j] < 0);
	}
	for(int i = 1; i <= N; i++){
		int nxt = -1;
		for(int j = 0; j < N; j++){
			if(abs(P[j]) == i) nxt = j;
			pnxt[j][i] = nxt;
		}
	}
	for(int i = 0; i < N; i++){
		nxt[i] = -1;
		for(int j = i - 1; j >= 0; j--){
			if(A[i] == A[j]){
				nxt[i] = j;
				break;
			}
		}
	}
	mint ret = 0;
	for(int i = N - 1; i >= 0; i--){
		for(int j = i + 1; j < N; j++){
			if(P[i] < 0 && P[j] > 0){
				if(abs(P[i]) != abs(P[j])){
					if(nxt[j] <= i) D[i][j] = mint(1);
					for(int k = i + 1; k < j; k++){
						if(nxt[k] > i || abs(P[i]) == abs(P[k])) continue;
						int st = max(k + 1, nxt[j]);
						if(st < j){
							D[i][j] += ES[k][j - 1] - ES[k][st - 1];
							if(pnxt[j - 1][abs(P[j])] >= st){
								D[i][j] -= ES2[k][pnxt[j - 1][abs(P[j])]];
							}
							if(pnxt[st - 1][abs(P[j])] >= 0){
								D[i][j] += ES2[k][pnxt[st - 1][abs(P[j])]];
							}
						}
					}
				}
				E[i][j] = D[i][j];
				for(int l = i + 1; l < j; l++){
					int st = max(i + 1, nxt[l]);
					if(st < l){
						E[i][j] += (DS[l - 1] - DS[st - 1]) * E[l][j];
						E[i][j] -= (DS2[l - 1][abs(P[l])] - DS2[st - 1][abs(P[l])]) * E[l][j];
					}
				}
			}
			if(nxt[i] < 0) ret += E[i][j];
			DS[j] = DS[j - 1] + D[i][j];
			for(int k = 0; k <= N; k++){
				DS2[j][k] = DS2[j-1][k] + (abs(P[j]) == k ? D[i][j] : mint(0));
			}
			ES[i][j] = ES[i][j-1] + E[i][j];
			ES2[i][j] = (pnxt[j - 1][abs(P[j])] >= 0 ? ES2[i][pnxt[j - 1][abs(P[j])]] : mint(0)) + E[i][j];
		}
	}
	return ret;
}

