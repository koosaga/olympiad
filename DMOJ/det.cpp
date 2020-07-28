// Ivan Carvalho
// Solution to https://dmoj.ca/problem/det
#include <cstdio>
typedef long long ll;
const int MAXN = 501;
const ll MOD = 1e9 + 7;
inline ll add(ll a,ll b){
	ll val = (a + b) %MOD;
	if(val < 0) val += MOD;
	return val;
}
inline ll sub(ll a,ll b){
	ll val = (a-b) % MOD;
	if(val < 0) val += MOD;
	return val;
}
inline ll mul(ll a,ll b){
	ll val = (a*b) % MOD;
	if(val < 0) val += MOD;
	return val;
}
inline ll sq(ll a){
	return mul(a,a);
}
ll fast_expo(ll z,ll expo){
	if(expo == 0) return 1LL;
	if(expo == 1) return z % MOD;
	if(expo % 2 == 0){
		return  sq(fast_expo(z,expo/2));
	}
	return mul(z,fast_expo(z,expo-1));
}
ll inv(ll z){
	return fast_expo(z,MOD - 2);
}
ll matriz[MAXN][MAXN];
int n;
void exibe(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%lld ",matriz[i][j]);
		}
		printf("\n");
	}
}
int main(){
	scanf("%d",&n);
	ll fora = 1LL;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%lld",&matriz[i][j]);
			matriz[i][j] = (matriz[i][j] + MOD) % MOD;
		}
	}
	for(int linha = 1;linha<=n-1;linha++){
		if(matriz[linha][linha] == 0){
			int achou = -1;
			for(int proxlinha = linha+1;proxlinha<=n;proxlinha++){
				if(matriz[proxlinha][linha] != 0){
					achou = proxlinha;
					break;
				}
			}
			if(achou == -1){
				printf("0\n");
				return 0;
			}
			for(int coluna = 1;coluna<=n;coluna++) matriz[linha][coluna] = add(matriz[linha][coluna],matriz[achou][coluna]);
		}
		ll divisor = inv(matriz[linha][linha]);
		fora = mul(fora,matriz[linha][linha]);
		//printf("F %lld D %lld\n",fora,divisor);
		for(int coluna = linha;coluna<=n;coluna++) matriz[linha][coluna] = mul(matriz[linha][coluna],divisor);
		//exibe();
		for(int proxlinha = linha+1;proxlinha<=n;proxlinha++){
			ll cof = matriz[proxlinha][linha];
			for(int coluna = 1;coluna<=n;coluna++) matriz[proxlinha][coluna] = sub(matriz[proxlinha][coluna], cof*matriz[linha][coluna] );
		}
		//exibe();
	}
	for(int linha=1;linha<=n;linha++) fora = mul(fora,matriz[linha][linha]);
	fora += MOD;
	fora %= MOD;
	printf("%lld\n",fora);
	return 0;
}",fora);
	return 0;
}