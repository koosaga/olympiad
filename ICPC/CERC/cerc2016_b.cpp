#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const lint inf = 1e18;

int n, m, t;
char str[22][22];
int a[22], b[22];
int d1[1<<20], d2[1<<20];
int pcnt[1<<20];

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++) cin >> str[i];
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<m; i++) cin >> b[i];
	for(int i=1; i<(1<<20); i++){
		pcnt[i] = pcnt[i - (i & -i)] + 1;
	}
	vector<int> v1, v2;
	cin >> t;
	d1[0] = d2[0] = 1;
	for(int i=1; i<(1<<n); i++){
		int nei = 0, cnt = 0;
		d1[i] = 1;
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				if(d1[i ^ (1<<j)] == 0) d1[i] = 0;
				for(int k=0; k<m; k++){
					if(str[j][k] == '1') nei |= (1<<k);
				}
			}
		}
		if(pcnt[nei] < pcnt[i]) d1[i] = 0;
	}
	for(int i=1; i<(1<<m); i++){
		int nei = 0, cnt = 0;
		d2[i] = 1;
		for(int j=0; j<m; j++){
			if((i >> j) & 1){
				if(d2[i ^ (1<<j)] == 0) d2[i] = 0;
				for(int k=0; k<n; k++){
					if(str[k][j] == '1') nei |= (1<<k);
				}
			}
		}
		if(pcnt[nei] < pcnt[i]) d2[i] = 0;
	}
	for(int i=0; i<(1<<n); i++){
		int cnt = 0;
		if(d1[i]){
			for(int j=0; j<n; j++){
				if((i >> j) & 1) cnt+= a[j];
			}
			v1.push_back(cnt);
		}
	}
	for(int i=0; i<(1<<m); i++){
		int cnt = 0;
		if(d2[i]){
			for(int j=0; j<m; j++){
				if((i >> j) & 1) cnt += b[j];
			}
			v2.push_back(cnt);
		}
	}
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	lint ans = 0;
	for(auto &i : v1){
		ans += v2.end() - lower_bound(v2.begin(), v2.end(), t - i);
	}
	cout << ans;
}
