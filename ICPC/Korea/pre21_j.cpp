#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 305;

int n, m, a[MAXN][MAXN];

int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			int x; cin >> x;
			a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + x;
		}
	}
	int ret = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			for(int k = i; k <= min(i+9, n); k++){
				for(int l = j; l <= min(j+9, m); l++){
					int m = a[k][l] - a[i-1][l] - a[k][j-1] + a[i-1][j-1];
					if(m == 10) ret++;
				}
			}
		}
	}
	cout << ret << endl;
}
