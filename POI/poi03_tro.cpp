#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int bino[3][3];

int ncr(lint x, lint y){
	if(x == 0) return y == 0;
	return ncr(x/3, y/3) * bino[x%3][y%3] % 3;
}

int main(){
	for(int i=0; i<3; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
		}
	}
	int t;
	cin >> t;
	while(t--){
		lint n, k;
		scanf("%lld %lld",&n,&k);
		int dap = ncr(2 * n, k);
		if(k % 2 == 1) dap = 3 - dap;
		printf("%d\n", dap % 3);
	}
}
