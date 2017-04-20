#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[1005];

bool solve(){
	if(*max_element(a, a+n) == 0) return false;
	for(int i=0; i<n; i++){
		int prv = a[i];
		for(int j=(i ? a[i-1] : 0); j<a[i]; j++){
			a[i] = j;
			bool ans = !solve();
			a[i] = prv;
			if(ans) return true;
		}
	}
	return false;
}

int main(){
	int tc;
	cin >> tc;
	while(tc--){
		cin >> n;
		int sum = 0;
		for(int i=1; i<=n; i++){
			cin >> a[i];
		}
		for(int i=n-1; i>=0; i-=2){
			sum ^= a[i+1] - a[i];
		}
		puts(sum == 0 ? "NIE" : "TAK");
	}
}
