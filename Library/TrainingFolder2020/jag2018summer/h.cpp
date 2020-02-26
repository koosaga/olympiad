#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 2000005;
const int mod = 1e9 + 7;

int n;
char str[MAXN];
lint pwr[MAXN];
int fail[MAXN];

int main(){
	scanf("%s", str);
	n = strlen(str);
	pwr[0] = 1;
	int p = 0;
	for(int i=1; i<=2*n; i++) pwr[i] = pwr[i-1] * 26 % mod;
	for(int i=1; i<n; i++){
		while(p && str[i] != str[p]) p = fail[p];
		if(str[i] == str[p]) p++;
		fail[i + 1] = p;
	}
	lint ret = pwr[n];
	for(int i=1; i<=n; i++){
		if(fail[i] == 0) ret += mod - pwr[n - i];
	}
	cout << ret % mod << endl;
}

