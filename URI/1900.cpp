// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1900
#include <cstdio>
#include <unordered_map>
using namespace std;
typedef long long ll;
#define gc getchar_unlocked
void getint(ll &x){
    register ll c = gc();
    x = 0;
    ll neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
ll n,resp,total;
unordered_map<ll,ll> frequencia;
int main(){
	frequencia[0LL] = 1LL;
	getint(n);
	for(ll i=1;i<=n;i++){
		ll davez;
		getint(davez);
		total += davez;
		//printf("%lld %lld\n",frequencia[total],total);
		resp += frequencia[total];
		frequencia[total]++;
	}
	printf("%lld\n",resp);
	return 0;
}
