#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, q;
lint a[100005], b[100005], c[100005];

int main(){
	cin >> n >> q;
	for(int i=0; i<n; i++) scanf("%lld",&a[i]);
	if(q) sort(a, a+n);
	while(q--){
		int l, r, x;
		cin >> l >> r >> x;
		l--, r--;
		int p = 0, q = 0;
		for(int i=0; i<n; i++){
			if(i >= l && i <= r) b[p++] = a[i] + x;
			else c[q++] = a[i];
		}
		merge(b, b+p, c, c+q, a);
	}
	for(int i=0; i<n; i++) printf("%lld ", a[i]);
}
