// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SABBIRGAME/
#include <cstdio>
typedef long long ll;
const int MAXN = 1e3 + 1;
const ll INF = 1e10 + 1;
const ll NEG = -INF;
int TC,n,val[MAXN];
int main(){
	scanf("%d",&TC);
	while(TC--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&val[i]);
		}
		ll ini = 0, fim = INF, resp = -1,meio;
		while(ini <= fim){
			meio = (ini+fim)/2;
			ll temp = meio;
			for(int i=1;i<=n;i++){
				temp += val[i];
				if(temp <= 0) temp = NEG;
			}
			if(temp > 0){
				fim = meio - 1;
				resp = meio;
			}
			else ini = meio + 1;
		}
		printf("%lld\n",resp);
	}
	return 0;
}