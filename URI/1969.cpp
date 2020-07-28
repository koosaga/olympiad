// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1969
#include <cstdio>
#define MAXN 100010
typedef long long ll;
const ll MODULO = 1e9 + 7;
ll arvore[4*MAXN],vetor[MAXN],n,q;
char entrada[20];
struct Matrix{ll mat[2][2];};
Matrix base,identidade;
Matrix multiplication(Matrix A,Matrix B){
	Matrix C;
	for(ll i=0;i<2;i++){
		for(ll j=0;j<2;j++){
			C.mat[i][j] = 0;
			for(ll k=0;k<2;k++){
				C.mat[i][j] += (A.mat[i][k]*B.mat[k][j]) % MODULO;
				C.mat[i][j] %= MODULO;
			}
		}
	}
	return C;
}
Matrix exponentiation(ll expo){
	if(expo == 0) return identidade;
	if(expo == 1) return base;
	if(expo % 2 == 0){
		Matrix temp = exponentiation(expo/2);
		return multiplication(temp,temp);
	}
	return multiplication(base,exponentiation(expo-1));
}
ll fibonnaci(ll nth){
	Matrix resultado = exponentiation(nth);
	return resultado.mat[0][0];
}
void build(ll pos,ll left,ll right){
	if(left == right){
		arvore[pos] = vetor[left];
		return;
	}
	ll mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = (arvore[2*pos]*arvore[2*pos+1]) % MODULO;
}
void update(ll pos,ll left,ll right,ll x){
	if(left > right || left > x || right < x) return;
	if(left == x &&  right == x){
		arvore[pos] = vetor[x];
		return;
	}
	ll mid = (left+right)/2;
	update(2*pos,left,mid,x);
	update(2*pos+1,mid+1,right,x);
	arvore[pos] = (arvore[2*pos]*arvore[2*pos+1]) % MODULO;
}
ll query(ll pos,ll left,ll right,ll i,ll j){
	if(left > right || left > j || right < i) return 1;
	if(left >= i &&  right <= j){
		return arvore[pos];
	}
	ll mid = (left+right)/2;
	return (query(2*pos,left,mid,i,j)*query(2*pos+1,mid+1,right,i,j)) % MODULO;
}
int main(){
	scanf("%lld %lld",&n,&q);
	for(ll i=0;i<2;i++){
		for(ll j=0;j<2;j++){
			identidade.mat[i][j] = (i==j);
			base.mat[i][j] = 1;
		}
	}
	base.mat[1][1] = 0;
	for(ll i=1;i<=n;i++){
		ll davez;
		scanf("%lld",&davez);
		vetor[i] = fibonnaci(davez-2);
	}
	build(1,1,n);
	while(q--){
		scanf("%s",entrada);
		if(entrada[1] == '>'){
			ll a,b;
			scanf("%lld %lld",&a,&b);
			printf("%lld\n",query(1,1,n,a,b));
		}
		else if(entrada[1] == '-'){
			ll pos,val;
			scanf("%lld %lld",&pos,&val);
			vetor[pos] = fibonnaci(val-2);
			//printf("%lld\n",fibonnaci(val-2));
			update(1,1,n,pos);
		}
	}
	printf("%lld\n",query(1,1,n,1,n));
	return 0;
}
