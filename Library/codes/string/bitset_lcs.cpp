#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using word = unsigned long long;
using pi = pair<int, int>;
const int MAXN = 100005;

struct bset{
	vector<word> wd;
	bset(){}
	bset(int n){
		wd.resize(n / 64 + 2);
	}
	void set(int x){
		wd[x >> 6] |= (word(1) << (x & 63));
	}
	void reset(int x){
	    wd[x >> 6] = 0;
	}
	bool get(int x){
		return (wd[x >> 6] >> (x & 63)) & 1;
	}
	bset operator-(const bset &b){
		assert(sz(b.wd) == sz(wd));
		bset ret; ret.wd.resize(sz(wd));
		bool carry_bit = 0;
		for(int i=0; i<sz(wd); i++){
			ret.wd[i] = wd[i] - (b.wd[i] + carry_bit);
			carry_bit = (ret.wd[i] > wd[i] || (ret.wd[i] == wd[i] && carry_bit));
		}
		return ret;
	}
	bset operator^(const bset &b){
		assert(sz(b.wd) == sz(wd));
		bset ret; ret.wd.resize(sz(wd));
		for(int i=0; i<sz(wd); i++){
			ret.wd[i] = wd[i] ^ b.wd[i];
		}
		return ret;
	}
	bset operator|(const bset &b){
		bset ret; ret.wd.resize(sz(b.wd));
		for(int i=0; i<sz(b.wd); i++){
			ret.wd[i] = wd[i] | b.wd[i];
		}
		return ret;
	}
	bset operator&(const bset &b){
		assert(sz(b.wd) == sz(wd));
		bset ret; ret.wd.resize(sz(wd));
		for(int i=0; i<sz(wd); i++){
			ret.wd[i] = wd[i] & b.wd[i];
		}
		return ret;
	}
	void shift(){
		for(int i=sz(wd)-1; i>=0; i--){
			wd[i] <<= 1;
			if(i && (wd[i - 1] >> 63)) wd[i] ^= 1;
		}
	}
};

string s, t, ans;
bset alph[26];

vector<int> get_lcs(string s, string t){
	int n = sz(s);
	int m = sz(t);
	bool use[26] = {};
	for(int i=0; i<m; i++){
	    use[t[i] - 'A'] = 1;
		alph[t[i] - 'A'].set(i + 1);
	}
	bset B(sz(t));
	for(int i=0; i<n; i++){
		bset y = B; y.shift(); y.set(0);
		bset x = (use[s[i] - 'A'] ? (alph[s[i] - 'A'] | B) : B);
		B = x ^ (x & (x - y));
	}
	vector<int> cur(m + 1);
	int cnt = 0;
	for(int i=0; i<m; i++){
		if(B.get(i + 1)) cnt++;
		cur[i + 1] = cnt;
	}
	for(int i=0; i<m; i++){
		alph[t[i] - 'A'].reset(i + 1);
	}
	return cur;
}

void solve(int l1, int r1, int l2, int r2){
	if(r1 - l1 == 1){
		if(find(t.begin() + l2, t.begin() + r2, s[l1]) != t.begin() + r2) ans.push_back(s[l1]);
		return;
	}
	int m = (l1 + r1) / 2;
	string x = s.substr(l1, m - l1);
	string y = s.substr(m, r1 - m);
	string z = t.substr(l2, r2 - l2);
	auto tab1 = get_lcs(x, z);
	reverse(all(y));
	reverse(all(z));
	auto tab2 = get_lcs(y, z);
	reverse(all(tab2));
	pi ans(-1e9, 1e9);
	for(int i=0; i<=sz(z); i++){
		ans = max(ans, pi(tab1[i] + tab2[i], i + l2));
	}
	solve(l1, m, l2, ans.second);
	solve(m, r1, ans.second, r2);
}

int main(){
	cin >> s >> t;
	for(int i=0; i<26; i++) alph[i] = bset(sz(t));
	solve(0, sz(s), 0, sz(t));
	cout << sz(ans) << endl;
	cout << ans << endl;
}
