#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[3];

int main(){
	cin >> n;
	for(int i=0; i<3; i++) cin >> a[i];
	sort(a, a+3);
	for(int i=0; i<n; i++){
		int b[3] = {i, (i+1)%n, (i+2)%n};
		sort(b, b+3);
		if(a[0] == b[0] && a[1] == b[1] && a[2] == b[2]){
			puts("TAK");
			return 0;
		}
	}
	puts((n-3)%2 == 1 ? "TAK" : "NIE");
}
