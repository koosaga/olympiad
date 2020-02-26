#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

namespace solve{
	lint dp_sfx[MAXN][505];
	lint dp_pfx[MAXN][505];
	int n, mod, ptr, pivot;
	pi a[MAXN];
	void init(int MOD){
		pivot = 0;
		mod = MOD;
		fill(dp_pfx[0] + 1, dp_pfx[0] + mod, -1e18);
		fill(dp_sfx[1] + 1, dp_sfx[1] + mod, -1e18);
	}
	void add(int weight, int value){
		n++;
		a[n] = pi(weight, value);
		for(int j=0; j<mod; j++){
			dp_pfx[n][j] = max(dp_pfx[n-1][j], dp_pfx[n-1][(j + mod - weight%mod) % mod] + value);
		}
	}
	void remove(){
		ptr++;
	}
	lint query(int l, int r){
		if(ptr == n) return (l == 0 ? 0 : -1);
		if(ptr > pivot){
			pivot = n;
			fill(dp_sfx[pivot + 1] + 1, dp_sfx[pivot + 1] + mod, -1e18);
			dp_sfx[pivot + 1][0] = 0;
			for(int j=pivot; j>ptr; j--){
				for(int k=0; k<mod; k++){
					dp_sfx[j][k] = max(dp_sfx[j+1][k], dp_sfx[j+1][(k + mod - a[j].first%mod) % mod] + a[j].second);
				}
			}
			dp_pfx[pivot][0] = 0;
			fill(dp_pfx[pivot] + 1, dp_pfx[pivot] + mod, -1e18);
		}
		lint ans = -1;
		vector<lint> run(mod);
		priority_queue<pi> pq;
		int siz = r - l + 1;
		for(int i=0; i<siz; i++) pq.emplace(dp_pfx[n][i], i);
		for(int i=mod-1; i>=0; i--){
			pq.emplace(dp_pfx[n][i], i);
			while(sz(pq) && (pq.top().second + mod - i) % mod >=siz){
				pq.pop();
			}
			assert(sz(pq));
			run[i] = pq.top().first;
		}
		for(int j=0; j<mod; j++){
			int pos = (l - j + mod) % mod;
			ans = max(ans, dp_sfx[ptr+1][j] + run[pos]);
		}
		return ans;
	}
}

class Crypto {
public:    
    Crypto() {
        sm = cnt = 0;
        seed();
    }

    int decode(int z) {
        z ^= next();
        z ^= (next() << 8);
        z ^= (next() << 16);
        z ^= (next() << 22);
        return z;
    }

    void query(long long z) {
        const long long B = 425481007;
        const long long MD = 1000000007;
        cnt++;
        sm = ((sm * B % MD + z) % MD + MD) % MD;
        seed();
    }
private: 
    long long sm;
    int cnt;

    uint8_t data[256];
    int I, J;

    void swap_data(int i, int j) {
        uint8_t tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;    
    }

    void seed() {
        uint8_t key[8];
        for (int i = 0; i < 4; i++) {
            key[i] = (sm >> (i * 8));
        }
        for (int i = 0; i < 4; i++) {
            key[i+4] = (cnt >> (i * 8));
        }

        for (int i = 0; i < 256; i++) {
            data[i] = i;
        }
        I = J = 0;

        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + data[i] + key[i%8]) % 256;
            swap_data(i, j);
        }
    }

    uint8_t next() {
        I = (I+1) % 256;
        J = (J + data[I]) % 256;
        swap_data(I, J);
        return data[(data[I] + data[J]) % 256];
    }
};

int main() {
    int MOD, Q;
    scanf("%d %d", &MOD, &Q);
    solve::init(MOD);
    Crypto c;
    for (int i = 0; i < Q; i++) {
        int t, w, v, l, r;
        scanf("%d %d %d %d %d", &t, &w, &v, &l, &r);
        t = c.decode(t);
        w = c.decode(w);
        v = c.decode(v);
        l = c.decode(l);
        r = c.decode(r);
        if (t == 1) {
        	solve::add(w, v);
        } else {
        	solve::remove();
        }
        long long ans =  solve::query(l, r);
        c.query(ans);
        printf("%lld\n", ans);
    }
}


