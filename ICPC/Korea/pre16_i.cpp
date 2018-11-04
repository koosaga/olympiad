#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, lint> pi;

int n, a[1005];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	sort(a, a+n);
	for(int i=0; i<=n; i++){
		bool ok1 = 0, ok2 = 0;
		if(i == 0 || a[n-i] >= i) ok1 = 1;
		if(i == n || a[n-i-1] <= i) ok2 = 1;
		if(ok1 && ok2){
			printf("%d ", i);
		}
	}
}
