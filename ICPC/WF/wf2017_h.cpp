#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 10005;

int n, t, f[MAXN], ban[MAXN], ptr[MAXN], pos[MAXN];
pi a[MAXN];

int main(){
	cin >> n >> t;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		pos[i] = a[i].second;
	}
	sort(a, a+n);
	sort(pos, pos + n);
	for(int j=0; j<n; j++) f[j] = pos[j], ptr[j] = n;
	for(int i=n-1; i>=0; i--){
		for(int j=0; j<n; j++){
			if(a[i].second <= pos[j]){
				f[j] -= t;
				while(ptr[j] > i + 1 && f[j] < a[ptr[j] - 1].first) ptr[j]--;
				if(ptr[j] < n){
					f[j] = min(f[j], a[ptr[j]].first - ban[ptr[j]]);
				}
				if(f[j] < a[i].first){
					puts("no");
					return 0;
				}
				if(f[j] < a[i].first + t){
					ban[i] = max(ban[i], a[i].first + t - f[j]);
				}
			}
		}
		for(int j=i+1; j<n; j++){
			ban[i] = max(ban[i], ban[j] - (a[j].first - a[i].first));
		}
		for(int j=i+1; j<n; j++){
			if(a[j].first - ban[j] < a[i].first){
				ban[j] = max(ban[j], ban[i] + (a[j].first - a[i].first));
			}
		}
	}
	puts("yes");
}
