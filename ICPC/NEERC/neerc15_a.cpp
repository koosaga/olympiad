#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

int chk[2][MAXN];
lint rcnt, ccnt, rsum, csum;

int main(){
	int n, q;
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		rcnt++;
		ccnt++;
		rsum += i;
		csum += i;
	}
	while(q--){
		char str[5];
		int x;
		scanf("%s %d",str,&x);
		if(*str == 'R'){
			if(!chk[0][x]) rcnt--, rsum -= x;
			else{
				puts("0");
				continue;
			}
			chk[0][x] = 1;
			printf("%lld\n", ccnt * x + csum);
		}
		if(*str == 'C'){
			if(!chk[1][x]) ccnt--, csum -= x;
			else{
				puts("0");
				continue;
			}
			chk[1][x] = 1;
			printf("%lld\n", rcnt * x + rsum);
		}
	}
}

