#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 5005;
const int mod = 998244353;

char str[1005][1005];
char buf[1005];


int main(){
	int n, m;
	cin >> n >> m;
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		for(int j=0; j<m; j++){
			str[j][n-1-i] = buf[j];
		}
	}
	for(int i=0; i<m; i++) puts(str[i]);
}
