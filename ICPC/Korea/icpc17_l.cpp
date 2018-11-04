#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 300005;
const int mod = 1e9 + 7;

int n[3], m, p;
lint d[3][55];
int a[3];
vector<pi> gph[3][55];

int main(){
	memset(d, 0x3f, sizeof(d));
	cin >> p;
	for(int i=0; i<p; i++){
		cin >> n[i] >> m;
		for(int j=1; j<=n[i]; j++){
			int x;
			cin >> x;
			gph[i][j].push_back(pi(x, j));
		}
		for(int j=0; j<m; j++){
			int s, e, x;
			cin >> s >> e >> x;
			gph[i][s].push_back(pi(x, e));
		}
		cin >> a[i];
		d[i][1] = 0;
	}
	lint ans = 1e18;
	for(int i=1; i<=200000; i++){
		lint tmp = 0;
		for(int j=0; j<p; j++){
			lint nxt[55];
			fill(nxt, nxt + 55, 1e18);
			for(int k=1; k<=n[j]; k++){
				for(auto &l : gph[j][k]){
					nxt[l.second] = min(nxt[l.second], d[j][k] + l.first);
				}
			}
			for(int k=1; k<=n[j]; k++) d[j][k] = nxt[k];
			tmp += d[j][a[j]];
		}
		ans = min(ans, tmp);
	}
	cout << ans << endl;
}
