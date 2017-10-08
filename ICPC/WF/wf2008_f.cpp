#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int mod = 1e9 + 7;

int main(){
	int tc = 0;
	while(1){
		int n;
		cin >> n;
		if(n == 0) break;
		if(n < 4 || n % 2 == 1){
			printf("Case %d: 0\n", ++tc);
			continue;
		}
		n = (n - 4) / 2;
		lint c1 = 2, c2 = 1;
		for(int i=0; i<4; i++){
			c1 *= n + i;
			c1 /= i + 1;
		}
		for(int i=0; i<3; i++){
			c2 *= n + i + 1;
			c2 /= i + 1;
		}
		printf("Case %d: %lld\n", ++tc, c1 + c2);
	}
}
