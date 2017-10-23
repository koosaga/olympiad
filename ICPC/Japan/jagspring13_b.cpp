#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

string a, c;
int fail[505];
int d2[505][10];
pi dp[10005][505][2];

int nxt(int pos, int chr){
	if(pos == c.size()) pos = fail[pos];
	while(pos > 0 && c[pos] != chr + '0') pos = fail[pos];
	if(c[pos] == chr + '0') pos++;
	return pos;
}

void prep(){
	for(int i=0; i<=10004; i++){
		for(int j=0; j<=504; j++){
			dp[i][j][0] = dp[i][j][1] = pi(0 ,0);
		}
	}
	for(int i=a.size(); i>=0; i--){
		for(int j=0; j<=c.size(); j++){
			for(int k=0; k<2; k++){
				if(i == a.size()){
					if(k) dp[i][j][k] = pi(0, 0);
					else dp[i][j][k] = pi(j == c.size(), 1);
					continue;
				}
				lint fi = 0, se = 0;
				for(int l=0; l<10; l++){
					if(k && a[i] == l + '0'){
						auto x = dp[i+1][d2[j][l]][1];
						fi += x.first;
						se += x.second;
						break;
					}
					else{
						auto x = dp[i+1][d2[j][l]][0];
						fi += x.first;
						se += x.second;
					}
				}
				if(j == c.size()) fi += se;
				fi %= mod;
				se %= mod;
				dp[i][j][k] = pi(fi, se);
			}
		}
	}
}

pi f(int pos, int mat, int bnd){
	return dp[pos][mat][bnd];
}

lint solve(string x){
	a = x;
	prep();
	lint ret = 0;
	for(int i=0; i<a.size(); i++){
		if(i == 0){
			for(int j=0; j<10; j++){
				if(!j && i + 1 != a.size()) continue;
				if(a[0] < j + '0') continue;
				if(a[0] == j + '0'){
					ret += f(i+1, d2[0][j], 1).first;
				}
				if(a[0] > j + '0'){
					ret += f(i+1, d2[0][j], 0).first;
				}
			}
		}
		else{
			for(int j=0; j<10; j++){
				if(!j && i + 1 != a.size()) continue;
				ret += f(i+1, d2[0][j], 0).first;
			}
		}
	}
	ret %= mod;
	return ret;
}

int main(){
	string a, b;
	cin >> a >> b >> c;
	reverse(b.begin(), b.end());
	b[0]++;
	for(int i=0; b[i] > '9'; i++){
		b[i] -= 10;
		if(i + 1 < b.size()) b[i+1]++;
		else b.push_back('1');
	}
	reverse(b.begin(), b.end());
	int p = 0;
	for(int i=1; i<c.size(); i++){
		while(p && c[i] != c[p]) p = fail[p];
		if(c[i] == c[p]) p++;
		fail[i+1] = p;
	}
	for(int i=0; i<=c.size(); i++){
		for(int j=0; j<10; j++) d2[i][j] = nxt(i, j);
	}
	cout << (solve(b) - solve(a) + mod) % mod;
}
