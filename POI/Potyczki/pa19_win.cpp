#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
const int MAXN = 2005;
const int mod = 1e9 + 7;

int n, k, a[MAXN][MAXN];

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=i; j++){
			scanf("%d",&a[i+1-j][j]);
		}
	}
	int ret = 6969;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n+1-i; j++){
			if(i * j <= k) ret = min(ret, a[i][j]);
		}
	}
	cout << ret << endl;
}