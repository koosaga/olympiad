// Ivan Carvalho
// Solution to https://dmoj.ca/problem/phantom3
#include <cstdio>
typedef long long ll;
bool primo[100001],crivo[20000001];
ll a,b;
int main(){
	scanf("%lld %lld",&a,&b);
	for(ll i=2;i<100001;i++){
		if(primo[i] == 0){
			for(ll j = i*i;j<100001;j+=i){
				primo[j] = 1;
			}
			ll lo;
			if(a % i == 0){
				lo = a;
			}
			else{
				lo = a - (a % i) + i;
			}
			for(ll j=lo;j<b;j+=i) crivo[j-a] = 1;
			if(a <= i && i < b) crivo[i-a] = 0;
		}
	}
	if(a == 0){
		crivo[0] = 1;
	}
	if(a <= 1 && 1 <b){
		crivo[1 - a] = 1;
	}
	ll resp = 0;
	for(ll j = a;j<b;j++){
		if(crivo[j-a] == 0) resp++;
	}
	printf("%lld\n",resp);
	return 0;
}