#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 55;

int r, c, n;
int x[MAXN], y[MAXN], z[MAXN];

int main(){
	cin >> r >> c >> n;
	for(int i=0; i<n; i++) cin >> x[i] >> y[i] >> z[i];
	int ret = 0;
	for(int i=1; i<=r; i++){
		for(int j=1; j<=c; j++){
			int h = -1e9;
			for(int k=0; k<n; k++){
				h = max(h, z[k] - abs(x[k] - i) - abs(y[k] - j));
			}
			for(int k=0; k<n; k++){
				if(h > z[k] + abs(x[k] - i) + abs(y[k] - j)){
					puts("No");
					return 0;
				}
			}
			ret += h;
		}
	}
	cout << ret << endl;
}
