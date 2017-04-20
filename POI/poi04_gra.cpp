#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

int m, n, a[1000005], b[1000005];

int main(){
	scanf("%d %d",&m,&n);
	for(int i=0; i<n; i++) scanf("%d",&b[i]);
	b[n] = m+1;
	int cur = 0, ans = 0;
	for(int i=n-1; i>=0; i--){
		cur += b[i+1] - b[i] - 1;
		a[n-i-1] = cur;
	}
	vector<pi> v;
	int totnim = 0;
	for(int i=0; i<n; ){
		int e = i;
		while(e < n && a[i] == a[e]) e++;
		v.push_back(pi(a[i], e - i));
		if(a[i] % 2 == 1) totnim ^= e - i;
		i = e;
	}
	if(v[0].first == 1){
		cout << v[0].second;
		return 0;
	}
	for(int i=0; i<v.size(); i++){
		if(v[i].first == 2) continue;
		if(v[i].first % 2 == 0){
			if(i && v[i-1].first == v[i].first - 1){
				for(int j=1; j<=v[i].second; j++){
					int curnim = totnim ^ v[i-1].second ^ (v[i-1].second + j);
					if(curnim == 0) ans++;
				}
			}
			else{
				for(int j=1; j<=v[i].second; j++){
					int curnim = totnim ^ j;
					if(curnim == 0) ans++;
				}
			}
		}
		else{
			for(int j=1; j<=v[i].second; j++){
				int curnim = totnim ^ v[i].second ^ (v[i].second - j);
				if(curnim == 0) ans++;
			}
		}
	}
	cout << ans;
}
