#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

int n;
lint a[1000005], dp[1000005];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%lld",&a[i]);
	}
	sort(a, a+n);
	lint mx = 0;
	for(int i=0; i<n; i++){
		mx = max(mx, -mx + a[i]);
	}
	cout << mx;
}
