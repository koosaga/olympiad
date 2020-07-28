// Ivan Carvalho
// Solution to https://dmoj.ca/problem/gfssoc16s2
#include <cstdio>
typedef long long ll;
ll a,b;
int resp;
void func(ll val,ll num){
	ll v1 = (val) + 10LL*(1LL << (4LL*num));
	ll v2 = (val) + 12LL*(1LL << (4LL*num));
	ll v3 = (val) + 14LL*(1LL << (4LL*num));
	if(a <= v1 && v1 <= b) resp++;
	if(a <= v2 && v2 <= b) resp++;
	if(a <= v3 && v3 <= b) resp++;
	if(v1 < b) func(v1,num+1);
	if(v2 < b) func(v2,num+1);
	if(v3 < b) func(v3,num+1);
}
int main(){
	scanf("%lld %lld",&a,&b);
	func(0,0);
	printf("%d\n",resp);
	return 0;
}