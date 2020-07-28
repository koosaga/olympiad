// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SWERC14J/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const ll MOD1 = 1e9 + 9;
const ll prime1 = 999983;
const ll MOD2 = 1e9 + 7;
const ll prime2 = 999979;
const ll invprime1 = 943912055;
const ll invprime2 = 672490127;
const ll MOD3 = 1e9 + 21;
const ll prime3 = 1e6 + 3;
const ll invprime3 = 801275613LL;
const int MAXN = 2010;
 
int R1,C1,R2,C2,achou;
char entrada[MAXN];
ll linear_string1[MAXN],linear_string2[MAXN],linear_val31,linear_val32;
ll hash1[MAXN][MAXN],hash2[MAXN][MAXN],linear1[MAXN],linear2[MAXN];
ll pot1[MAXN],pot2[MAXN],pot3[MAXN],invpot1[MAXN],invpot2[MAXN],invpot3[MAXN];
 
ll get_hash1(int id,int a,int b){
	ll val = ((hash1[id][b] - hash1[id][a-1])*invpot1[a-1]) % MOD1;
	if(val < 0) val += MOD1;
	return val;
}
 
ll get_hash2(int id,int a,int b){
	ll val = ((hash2[id][b] - hash2[id][a-1])*invpot2[a-1])%MOD2;
	if(val < 0) val += MOD2;
	return val;
}
 
void solve(int ini,int fim){
	//printf("#######################\n");
	for(int i = 1;i<=R2;i++){
		linear1[i] = get_hash1(i,ini,fim);
		linear2[i] = get_hash2(i,ini,fim);
		//printf("%lld %lld\n",linear1[i],linear2[i]);
	}
	//printf("#######################\n");
	ll meu_val31 = 0,meu_val32 = 0;
	for(int i = 1;i<=R1;i++){
		meu_val31 = (meu_val31 +  pot3[i]*linear1[i]) % MOD3;
		meu_val32 = (meu_val32 + pot3[i]*linear2[i]) % MOD3;
	}
	//printf("%lld %lld\n",meu_val31,meu_val32);
	if(meu_val31 == linear_val31 && meu_val32 == linear_val32) achou++;
	for(int i = R1+1;i<=R2;i++){
		meu_val31 *= invprime3;
		meu_val31 %= MOD3;
		meu_val31 -= linear1[i - R1];
		meu_val32 *= invprime3;
		meu_val32 %= MOD3;
		meu_val32 -= linear2[i - R1];
		meu_val31 = (meu_val31 +  pot3[R1]*linear1[i]) % MOD3;
		meu_val32 = (meu_val32 + pot3[R1]*linear2[i]) % MOD3;
		if(meu_val31 < 0) meu_val31 += MOD3;
		if(meu_val32 < 0) meu_val32 += MOD3;
		//printf("%lld %lld\n",meu_val31,meu_val32);
		if(meu_val31 == linear_val31 && meu_val32 == linear_val32) achou++;
	}
	//printf("#######################\n");
}
 
int main(){
	scanf("%d %d %d %d",&R1,&C1,&R2,&C2);
	invpot1[0] = invpot2[0] = invpot3[0] = pot1[0] = pot2[0] = pot3[0] = 1;
	for(int i = 1;i<MAXN;i++){
		invpot1[i] = (invpot1[i-1]*invprime1) % MOD1;
		invpot2[i] = (invpot2[i-1]*invprime2) % MOD2;
		invpot3[i] = (invpot3[i-1]*invprime3) % MOD3;
		pot1[i] = (pot1[i-1] * prime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
		pot3[i] = (pot3[i-1]*prime3) % MOD3;
	}
	for(int i = 1;i<=R1;i++){
		scanf("%s",entrada);
		for(int j = 1;j<=C1;j++){
			linear_string1[i] = (linear_string1[i] + pot1[j]*entrada[j-1]) % MOD1;
			linear_string2[i] = (linear_string2[i] + pot2[j]*entrada[j-1]) % MOD2;
		}
		//printf("%lld %lld\n",linear_string1[i],linear_string2[i]);
		linear_val31 = (linear_val31 + linear_string1[i]*pot3[i]) % MOD3;
		linear_val32 = (linear_val32 + linear_string2[i]*pot3[i]) % MOD3;
	}
	//printf("%lld %lld\n",linear_val31,linear_val32);
	for(int i = 1;i<=R2;i++){
		scanf("%s",entrada);
		for(int j = 1;j<=C2;j++){
			hash1[i][j] = (hash1[i][j-1] + entrada[j-1]*pot1[j]) % MOD1;
			hash2[i][j] = (hash2[i][j-1] + entrada[j-1]*pot2[j]) % MOD2;
		}
	}
	for(int ini = 1,fim = C1;fim<=C2;ini++,fim++){
		solve(ini,fim);
	}
	printf("%d\n",achou);
	return 0;
} 
