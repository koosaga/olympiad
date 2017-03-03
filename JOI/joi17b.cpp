#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int n, m, k;
lint a, b, c, t, s[3005];
lint loc[3005];

int main(){
	cin >> n >> m >> k;
	cin >> a >> b >> c >> t;
	for(int i=1; i<=m; i++){
		cin >> s[i];
		s[i]--;
		if(t - b * s[i] < 0) loc[i] = -1;
		else loc[i] = (t - b * s[i]) / a;
	}
	for(int i=1; i<m; i++) loc[i] = min(loc[i], s[i+1] - s[i] - 1);
	loc[m] = min(loc[m], 0ll);
	for(int i=0; i<k-m; i++){
		lint val = 0, pos = -1;
		for(int j=1; j<m; j++){
			if(t - s[j] * b - (loc[j] + 1) * c < 0) continue;
			lint st = loc[j] + 1;
			lint ed = min(s[j+1] - s[j] - 1, 
					(t - s[j] * b - st * c) / a + st);
			if(val < ed - st + 1){
				val = ed - st + 1;
				pos = j;
			}
		}
		if(val > 0){
			loc[pos] += val;
		}
	}
	lint ans = 0;
	for(int i=1; i<=m; i++) ans += loc[i] + 1;
	cout << ans-1;
}
