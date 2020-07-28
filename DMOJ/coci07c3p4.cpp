// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c3p4
#include <cstdio>
#include <vector>
#include <map>
using namespace std;
typedef long long ll;
map<ll,ll> X,Y;
int main(){
	ll n,resp = 0;
	scanf("%lld",&n);
	vector<ll> A(n),B(n);
	for(ll i=0;i<n;i++){
		scanf("%lld %lld",&A[i],&B[i]);
		X[A[i]]++;
		Y[B[i]]++;
	}
	for(ll i=0;i<n;i++){
		ll v1 = X[A[i]]-1;
		ll v2 = Y[B[i]]-1;
		//printf("%lld %lld\n",v1,v2);
		resp += v1*v2;
	}
	printf("%lld\n",resp);
	return 0;
}