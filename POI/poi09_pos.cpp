#include "poslib.h"
#include <algorithm>
using namespace std;
int dp[400004];

int main() {
	int n, a, b;
	inicjuj(&n, &a, &b);
	for(int i=0; ; i++){
		if(i >= a) dp[i] += dp[i-a];
		if(i >= b) dp[i] += dp[i-b];
		dp[i] = max(dp[i], 1);
		if(dp[i] >= n){
			int l = 1, r = n;
			while(l < r){
				while(i && dp[i-1] >= r - l + 1) i--;
				if(pytaj('N', l + dp[i-a])){
					r = l + dp[i-a] - 1;
					i -= a;
				}
				else{
					l = l + dp[i-a];
					i -= b;
				}
			}
			odpowiedz(l);
			return 0;
		}
	}
}
