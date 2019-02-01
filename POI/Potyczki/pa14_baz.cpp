#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
typedef long long lint;

lint s[MAXN];
int n, a[MAXN];
vector<int> odd, even;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a, a+n);
	reverse(a, a+n);
	for(int i=0; i<n; i++){
		s[i] = (i ? s[i-1] : 0) + a[i];
		if(a[i] & 1) odd.push_back(i);
		else even.push_back(i);
	}
	int q; scanf("%d",&q);
	while(q--){
		int x;
		scanf("%d",&x);
		if(s[x-1] % 2 == 1){
			printf("%lld\n", s[x-1]);
			continue;
		}
		int dx = 2e9;
		auto l1 = lower_bound(odd.begin(), odd.end(), x);
		auto l2 = lower_bound(even.begin(), even.end(), x);
		if(l1 != odd.end() && l2 != even.begin()){
			dx = min(dx, a[*(l2 - 1)] - a[*l1]);
		}
		if(l2 != even.end() && l1 != odd.begin()){
			dx = min(dx, a[*(l1 - 1)] - a[*l2]);
		}
		if(dx > 2e9 - 100) puts("-1");
		else printf("%lld\n", s[x-1] - dx);
	}
}
