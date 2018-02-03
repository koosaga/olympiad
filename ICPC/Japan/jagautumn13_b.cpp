#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;

string a, b, c;
lint dp[55][2];

lint f(int cur, int cry){
	if(cur == a.size()) return cry == 0;
	if(~dp[cur][cry]) return dp[cur][cry];
	lint ret = 0;
	for(int i=0; i<=9; i++){
		if(a[cur] != '?' && a[cur] != i + '0') continue;
		for(int j=0; j<=9; j++){
			if(b[cur] != '?' && b[cur] != j + '0') continue;
			int fu = (i + j + cry) % 10;
			int ncry = (i + j + cry) / 10;
			if(c[cur] != '?' && c[cur] != fu + '0') continue;
			ret += f(cur + 1, ncry);
		}
	}
	ret %= mod;
	return dp[cur][cry] = ret;
}

lint solve(){
	int mx = max({a.size(), b.size(), c.size()});
	int cnt1 = mx - a.size(), cnt2 = mx - b.size(), cnt3 = mx - c.size();
	for(int i=0; i<cnt1; i++) a.push_back('0');
	for(int i=0; i<cnt2; i++) b.push_back('0');
	for(int i=0; i<cnt3; i++) c.push_back('0');
	memset(dp, -1, sizeof(dp));
	lint ans = f(0, 0);
	for(int i=0; i<cnt1; i++) a.pop_back();
	for(int i=0; i<cnt2; i++) b.pop_back();
	for(int i=0; i<cnt3; i++) c.pop_back();
	return ans;
}

char prvA, prvB, prvC;

bool doA(){
	prvA = a.back();
	if(a.back() != '?' && a.back() != '0') return false;
	a.back() = '0';
	return true;
}

bool doB(){
	prvB = b.back();
	if(b.back() != '?' && b.back() != '0') return false;
	b.back() = '0';
	return true;
}

bool doC(){
	prvC = c.back();
	if(c.back() != '?' && c.back() != '0') return false;
	c.back() = '0';
	return true;
}

void revA(){
	a.back() = prvA;
}

void revB(){
	b.back() = prvB;
}

void revC(){
	c.back() = prvC;
}

int main(){
    while(true){
        cin >> a;
        if(a == "0") break;
        cin >> b >> c;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        reverse(c.begin(), c.end());
        lint ans = 0;
        for(int i=0; i<8; i++){
            bool ok = 1;
            int buho = 1;
            if(i & 1) ok &= doA(), buho *= -1;
            if(i & 2) ok &= doB(), buho *= -1;
            if(i & 4) ok &= doC(), buho *= -1;
            if(ok) ans += solve() * buho;
            if(i & 1) revA();
            if(i & 2) revB();
            if(i & 4) revC();
        }
        ans %= mod;
        ans += mod;
        ans %= mod;
        cout << ans << endl;
    }
}

