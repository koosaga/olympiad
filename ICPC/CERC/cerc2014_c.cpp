#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;

void solve(){
	int n;
	scanf("%d",&n);
	for(int i=2; i*(i+1)/2<=n; i++){
		if(i % 2 == 1 && n % i == 0){
			if(n / i - i / 2 > 0){
				printf("%d = %d",n, n/i - i/2);
				for(int j=n/i-i/2+1; j<=n/i+i/2; j++){
					printf(" + %d",j);
				}
				puts("");
				return;
			}
		}
		else if(i % 2 == 0 && n % (i/2) == 0){
			int p = n / (i/2);
			if(p > 0 && p % 2 == 1){
				printf("%d = %d",n, p/2 - i/2 + 1);
				for(int j=p/2-i/2+2; j<=p/2+i/2; j++){
					printf(" + %d",j);
				}
				puts("");
				return;
			}
		}
	}
	puts("IMPOSSIBLE");
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
}