// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1841
#include <cstdio>
#include <vector>
#include <unordered_map>
using namespace std;
typedef long long ll;
const int MAXP = 664589;
const int MAXN = 1e7+1;
const int MODULO = 1e9 + 7;
vector<ll> primos;
unordered_map<ll,ll> conversao;
bool composto[MAXN];
ll arvore[4*MAXP],vetor[MAXP],contador,tamanho,N,p;
void build(ll pos,ll left,ll right){
	if(left == right){
		arvore[pos] = vetor[left]+1;
		return;
	}
	ll mid = (left+right)/2;
	build(2*pos+1,left,mid);
	build(2*pos+2,mid+1,right);
	arvore[pos] = (arvore[2*pos+1]*arvore[2*pos+2]) % MODULO;
}
void update(ll pos,ll left,ll right,ll x){
	if(left > right || left > x || right < x) return;
	if(left == x && right == x){
		arvore[pos] = (vetor[left]+1);
		return;
	}
	ll mid = (left+right)/2;
	update(2*pos+1,left,mid,x);
	update(2*pos+2,mid+1,right,x);
	arvore[pos] = (arvore[2*pos+1]*arvore[2*pos+2]) % MODULO;
}
ll query(ll pos,ll left,ll right,ll i,ll j){
	if(left > right || left > j || right < i) return 1;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	ll mid = (left+right)/2;
	return (query(2*pos+1,left,mid,i,j)*query(2*pos+2,mid+1,right,i,j)) % MODULO;
}
int main(){
	for(ll i=2;i<MAXN;i++){
		if(!composto[i]){
			conversao[i] = contador++;
			primos.push_back(i);
			for(ll j = i*i;j < MAXN;j += i){
				composto[j] = true; 
			}
		}
	}
	contador--;
	scanf("%lld",&N);
	for(ll i=0;i<=contador;i++){
		while(N % primos[i] == 0){
			N /= primos[i];
			vetor[i]++;
		}
	}
	build(0,0,contador);
	while(scanf("%lld",&p) != EOF){
		printf("%lld\n",query(0,0,contador,0,conversao[p]-1));
		vetor[conversao[p]]++;
		update(0,0,contador,conversao[p]);
	}
	return 0;
}
