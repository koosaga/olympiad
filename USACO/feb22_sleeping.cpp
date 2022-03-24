#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;

namespace miller_rabin{
    lint mul(lint x, lint y, lint mod){

    	return (__int128) x * y % mod; 
	}
	lint ipow(lint x, lint y, lint p){
		lint ret = 1, piv = x % p;
		while(y){
			if(y&1) ret = mul(ret, piv, p);
			piv = mul(piv, piv, p);
			y >>= 1;
		}
		return ret;
	}
	bool miller_rabin(lint x, lint a){
		if(x % a == 0) return 0;
		lint d = x - 1;
		while(1){
			lint tmp = ipow(a, d, x);
			if(d&1) return (tmp != 1 && tmp != x-1);
			else if(tmp == x-1) return 0;
			d >>= 1;
		}
	}
	bool isprime(lint x){
		for(auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
			if(x == i) return 1;
			if(x > 40 && miller_rabin(x, i)) return 0;
		}
		if(x <= 40) return 0;
		return 1;
	}
}

namespace pollard_rho{
	lint f(lint x, lint n, lint c){
		return (c + miller_rabin::mul(x, x, n)) % n;
	}
	void rec(lint n, vector<lint> &v){
		if(n == 1) return;
		if(n % 2 == 0){
			v.push_back(2);
			rec(n/2, v);
			return;
		}
		if(miller_rabin::isprime(n)){
			v.push_back(n);
			return;
		}
		lint a, b, c;
		while(1){
			a = rand() % (n-2) + 2;
			b = a;
			c = rand() % 20 + 1;
			do{
				a = f(a, n, c);
				b = f(f(b, n, c), n, c);
			}while(gcd(abs(a-b), n) == 1);
			if(a != b) break;
		}
		lint x = gcd(abs(a-b), n);
		rec(x, v);
		rec(n/x, v);
	}
	vector<lint> factorize(lint n){
		vector<lint> ret;
		rec(n, ret);
		sort(all(ret));
		return ret;
	}
};


vector<pi> factors;
vector<lint> dvs;
int nxt[60][111111];

void bktk(int x, lint v){
	if(x == sz(factors)) dvs.push_back(v);
	else{
		for(int i=0; i<=factors[x].second; i++){
			bktk(x + 1, v);
			v *= factors[x].first;
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	srand(0x1557);
	int n; cin >> n;
	lint sum = 0;
	vector<lint> a;
	for(int i = 0; i < n; i++){
		lint x; cin >> x;
		sum += x;
		a.push_back(sum);
	}
	for(int i = 0; i < sz(a) - 1; i++) a[i] = gcd(a[i], a[n-1]);
	lint S = a[n - 1];
	sort(all(a));

	auto fact = pollard_rho::factorize(S);
	for(int i = 0; i < sz(fact); ){
		int e = i;
		while(e < sz(fact) && fact[e] == fact[i]) e++;
		factors.emplace_back(fact[i], e - i); i = e;
	}
	bktk(0, 1);
	sort(dvs.begin(), dvs.end());
	memset(nxt, -1, sizeof(nxt));

	for(int i = 0; i < sz(dvs); i++){
		for(int j = 0; j < sz(factors); j++){
			if(dvs[i] > S / factors[j].first) continue;
			if(S % (dvs[i] * factors[j].first)) continue;
			auto l = lower_bound(all(dvs), dvs[i] * factors[j].first);
			nxt[j][i] = l - dvs.begin();
		}
	}
	int exp = 0;
	vector<lint> ans(sz(dvs));
	sum = 0;
	vector<int> v(sz(dvs));
	for(int i = 0; i < sz(dvs); i++){
		lint x = dvs[i];
		int ptr = 1;
		for(int j = 0; j < sz(factors); j++){
			int cnt = 0;
			while(x % factors[j].first == 0){
				x /= factors[j].first;
				cnt++;
			}
			int cur = ptr;
			for(int i = 1; i <= cnt * cur; i++){
				v[ptr] = nxt[j][v[ptr - cur]]; ptr++;
			}
		}
		lint k = upper_bound(all(a), dvs[i]) - lower_bound(all(a), dvs[i]);
		for(int j = 0; j < ptr; j++) ans[v[j]] += k;
	}

	int q; cin >> q;
	while(q--){
		lint y; cin >> y;
		if(S % y){
			cout << "-1\n";
			continue;
		}
		lint iy = lower_bound(all(dvs), y) - dvs.begin();
		lint tot = n + S / y - 2 * ans[iy];
		cout << tot << "\n";
	}
}
