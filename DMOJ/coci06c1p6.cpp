// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c1p6
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
const int MAXN = 310;

ll pref1[MAXN][MAXN],pref2[MAXN][MAXN],suf1[MAXN][MAXN],suf2[MAXN][MAXN];
ll linear1[MAXN],linear2[MAXN],reto1[MAXN],reto2[MAXN];
ll pot1[MAXN],pot2[MAXN],pot3[MAXN],invpot1[MAXN],invpot2[MAXN],invpot3[MAXN];
int N,M,melhor;
char entrada[MAXN];

ll get_pref1(int id,int a,int b){
	ll val = ((pref1[id][b] - pref1[id][a-1])*invpot1[a-1]) % MOD1;
	if(val < 0) val += MOD1;
	return val;
}

ll get_pref2(int id,int a,int b){
	ll val = ((pref2[id][b] - pref2[id][a-1]) * invpot2[a-1]) % MOD2;
	if(val < 0) val += MOD2;
	return val;
}

ll get_suf1(int id,int a,int b){
	ll val = ((suf1[id][a] - suf1[id][b+1]) * invpot1[M - b]) % MOD1;
	if(val < 0) val += MOD1;
	return val;
}

ll get_suf2(int id,int a,int b){
	ll val = ((suf2[id][a] - suf2[id][b+1]) * invpot2[M - b]) % MOD2;
	if(val < 0) val += MOD2;
	return val;
}

int checa(int coluna,int tamanho){
	if(tamanho > N || coluna + tamanho - 1 > M || tamanho <= melhor) return 0;
	ll f31 = 0, f32 = 0, g31 = 0,g32 = 0;
	for(int i = 1;i<=tamanho;i++){
		linear1[i] = get_pref1(i,coluna,coluna + tamanho - 1);
		linear2[i] = get_pref2(i,coluna,coluna + tamanho - 1);
		reto1[i] = get_suf1(i,coluna,coluna + tamanho - 1);
		reto2[i] = get_suf2(i,coluna,coluna + tamanho - 1);
		f31 = (f31 + linear1[i]*pot3[i]) % MOD3;
		f32 = (f32 + linear2[i]*pot3[i]) % MOD3;
		g31 = (g31 + reto1[i]*pot3[tamanho - i + 1]) % MOD3;
		g32 = (g32 + reto2[i]*pot3[tamanho - i + 1]) % MOD3;
	}
	if(f31 == g31 && f32 == g32) return 1;
	for(int i = tamanho+1;i<=N;i++){
		linear1[i] = get_pref1(i,coluna,coluna + tamanho - 1);
		linear2[i] = get_pref2(i,coluna,coluna + tamanho - 1);
		reto1[i] = get_suf1(i,coluna,coluna + tamanho - 1);
		reto2[i] = get_suf2(i,coluna,coluna + tamanho - 1);
		f31 = (f31 * invprime3 - linear1[i - tamanho]) % MOD3;
		f32 = (f32 * invprime3 - linear2[i - tamanho]) % MOD3;
		f31 = (f31 + linear1[i]*pot3[tamanho]) % MOD3;
		f32 = (f32 + linear2[i]*pot3[tamanho]) % MOD3;
		if(f31 < 0) f31 += MOD3;
		if(f32 < 0) f32 += MOD3;
		g31 = (g31 - reto1[i - tamanho]*pot3[tamanho] + reto1[i]) % MOD3;
		g31 = (g31 * prime3) % MOD3;
		g32 = (g32 - reto2[i - tamanho]*pot3[tamanho] + reto2[i]) % MOD3;
		g32 = (g32 * prime3) % MOD3;
		if(g31 < 0) g31 += MOD3;
		if(g32 < 0) g32 += MOD3;
		if(f31 == g31 && f32 == g32) return 1;
	}
	return 0;
}

int main(){
	invpot1[0] = invpot2[0] = invpot3[0] = pot1[0] = pot2[0] = pot3[0] = 1;
	for(int i = 1;i<MAXN;i++){
		pot1[i] = (pot1[i-1]*prime1) % MOD1;
		pot2[i] = (pot2[i-1]*prime2) % MOD2;
		pot3[i] = (pot3[i-1]*prime3) % MOD3;
		invpot1[i] = (invpot1[i-1]*invprime1) % MOD1;
		invpot2[i] = (invpot2[i-1]*invprime2) % MOD2;
		invpot3[i] = (invpot3[i-1]*invprime3) % MOD3;
	}
	scanf("%d %d",&N,&M);
	for(int i = 1;i<=N;i++){
		scanf("%s",entrada);
		for(int j = 1;j<=M;j++){
			pref1[i][j] = (pref1[i][j-1] + pot1[j]*entrada[j-1]) % MOD1;
			pref2[i][j] = (pref2[i][j-1] + pot2[j]*entrada[j-1]) % MOD2;
		}
		for(int j = M;j>=1;j--){
			suf1[i][j] = (suf1[i][j+1] + pot1[M - j + 1]*entrada[j-1]) % MOD1;
			suf2[i][j] = (suf2[i][j+1] + pot2[M - j + 1]*entrada[j-1]) % MOD2;
		}
	}
	for(int coluna = 1;coluna<=M;coluna++){
		for(int tamanho = 2;tamanho<=M;tamanho++){
			if(checa(coluna,tamanho)) melhor = max(melhor,tamanho);
		}
	}
	if(melhor == 0) melhor = -1;
	printf("%d\n",melhor);
	return 0;
}