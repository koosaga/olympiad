#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int n;
string str[55];
int d1[55][55][22][27];
int d2[55][55][22][27];

bool ok(int s, int e, int x, int p){
	if(~d1[s][e][x][p]) return d1[s][e][x][p];
	if(p == 0){
		for(int i=s; i<=e; i++){
			if(str[i].size() > x) return d1[s][e][x][p] = 0;
		}
		return d1[s][e][x][p] = 1;
	}
	for(int i=s; i<=e; i++){
		if(str[i].size() <= x) return d1[s][e][x][p] = 0;
		if(str[i][x] != '?' && str[i][x] != 'a' - 1 + p) return d1[s][e][x][p] = 0;
	}
	return d1[s][e][x][p] = 1;
}

int g(int s, int e, int x, int p){
	if(s > e) return 1;
	if(p == -1) return 0;
	if(x > 20) return s == e;
	if(~d2[s][e][x][p]) return d2[s][e][x][p];
	int ret = 0;
	for(int i=s; i<=e+1; i++){
		if(ok(i, e, x, p)){
			ret += 1ll * g(s, i-1, x, p-1) * g(i, e, x+1, 26) % mod;
			ret %= mod;
		}
	}
	return d2[s][e][x][p] = ret;
}

int main(){
	memset(d1, -1, sizeof(d1));
	memset(d2, -1, sizeof(d2));
	cin >> n;
	for(int i=0; i<n; i++) cin >> str[i];
	cout << g(0, n-1, 0, 26);
}

