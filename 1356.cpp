// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1356
#include <cstdio>
#include <cstring>
#define MAXN 100010
#define LSOne(S) (S & -S)
typedef long long ll;
ll vetor[MAXN],bit[MAXN],B,MODULO,L,N;
ll fast_expo(ll base, ll expo){
	if(expo == 0LL) return 1LL;
	if(expo == 1LL) return base % MODULO;
	if(expo % 2LL  == 0LL){
		ll temp = fast_expo(base,expo/2LL);
		return (temp*temp % MODULO);
	}
	return (base*fast_expo(base,expo-1LL)) % MODULO;
}
ll inv(ll val){
	return fast_expo(val%MODULO,MODULO-2LL);
}
void update(ll pos,ll val){
	while(pos <= L){
		bit[pos] += val;
		bit[pos] %= MODULO;
		pos += LSOne(pos);
	}
}
ll sum(ll pos){
	ll ans = 0;
	while(pos > 0){
		ans += bit[pos];
		ans %= MODULO;
		pos -= LSOne(pos);
	}
	return ans;
}
ll query(ll ini,ll fim){
	ll val = (((sum(fim) - sum(ini-1)) % MODULO) + MODULO) % MODULO;
	ll divide = inv(fast_expo(B,L - fim + 1));
	return (val*divide)%MODULO;
}
int main(){
	while(scanf("%lld %lld %lld %lld",&B,&MODULO,&L,&N) && (B||MODULO||L||N)){
		memset(bit,0LL,sizeof(bit));
		memset(vetor,0LL,sizeof(vetor));
		while(N--){
			char op;
			scanf(" %c",&op);
			if(op == 'E'){
				ll pos,val;
				scanf("%lld %lld",&pos,&val);
				update(pos,-vetor[pos]);
				vetor[pos] = (fast_expo(B,L - pos + 1LL)*val)%MODULO;
				update(pos,vetor[pos]);
			}
			if(op == 'H'){
				ll ini,fim;
				scanf("%lld %lld",&ini,&fim);
				printf("%lld\n",query(ini,fim));
			}
		}
		//for(ll i=1;i<=L;i++){
		//	printf("%lld ",(((sum(i) - sum(i-1)) % MODULO) + MODULO) % MODULO);
		//}
		//printf("\n");
		printf("-\n");
	}
	return 0;
}
