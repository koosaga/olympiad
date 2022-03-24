#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 2505;
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

lint dp[MAXN][MAXN], aux[MAXN][MAXN];
int nxt[MAXN][MAXN];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n; string s; cin >> n >> s;
	lint A, B, C; cin >> A >> B >> C;
	memset(aux, 0x3f, sizeof(aux));
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j <= n; j++) dp[i][j] = 1e18;
	}
	{
		vector<int> sfx(n); iota(all(sfx), 0);
		sort(all(sfx), [&](const int &a, const int &b){
			return s.substr(a) < s.substr(b);
		});
		vector<int> lcp(n);
		for(int i = 1; i < n; i++){
			int p = sfx[i-1], q = sfx[i];
			while(p + lcp[i] < n && q + lcp[i] < n && s[p + lcp[i]] == s[q + lcp[i]]) lcp[i]++;
		}
		for(int l = 1; l <= n; l++){
			for(int j = 0; j < sz(sfx); ){
				int k = j + 1;
				while(k < sz(sfx) && lcp[k] >= l) k++;
				vector<int> v;
				for(int x = j; x < k; x++){
					v.push_back(sfx[x]);
				}
				sort(all(v));
				{
					int j = 0;
					for(int i = 0; i < sz(v); i++){
						while(j < i && v[j] <= v[i] - l) j++;
						if(j > 0) nxt[v[i]][l] = v[j - 1];
						else nxt[v[i]][l] = -1;
					}
				}
				j = k;
			}
		}
	}
	for(int i = 0; i <= n; i++){
		for(int j = 0; j + i <= n; j++){
			int s = j, e = j + i;
			dp[s][e] = min(dp[s][e], aux[s][e]);
			aux[s - 1][e] = min(aux[s - 1][e], aux[s][e] + A);
			dp[s][e + 1] = min(dp[s][e + 1], dp[s][e] + A);
			if(s < e){
				int p = s;
				int cur_proc = s - 1;
				int match = 1;
				while(cur_proc >= 0){
					aux[cur_proc][e] = min(aux[cur_proc][e], dp[s][e] + B + match * C + A * (e - cur_proc - match * i));
					match++;
					cur_proc = nxt[p][i];
					p = nxt[p][i];
				}
			}
		}
	}
	cout << dp[0][n] << endl;
}
