#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long lint;
 
lint n, m;
lint ret, tmp = 1;
 
int main(){
	scanf("%lld %lld",&n,&m);
	for(lint i=n; i>=0; i--){
		if(i%2 == 1){
			ret += tmp;
		}
		else{
			ret += m - tmp;
		}
		tmp *= max(i,1ll) % m;
		if(max(i,1ll) % m == 0) break;
		tmp %= m;
		ret %= m;
	}
	ret *= ret;
	ret %= m;
	printf("%lld",ret);
}