// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tsoc15c2p6
#include <cstdio>
#include <algorithm>
#define MAXN 30100
#define NULO 1000000000
using namespace std;
typedef long long ll;
ll arvore[4*MAXN],lazy[4*MAXN],vetor[MAXN];
void build(ll pos,ll left,ll right){
	if(left == right){
		arvore[pos] = vetor[left];
		return;
	}
	ll mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = min(arvore[2*pos],arvore[2*pos+1]);
}
void propagate(ll pos,ll left,ll right){
	if(lazy[pos] == 0) return;
	arvore[pos] -= lazy[pos];
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
}
void update(ll pos,ll left,ll right,ll i,ll j,ll val){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos] = val;
		propagate(pos,left,right);
		return;
	}
	ll mid = (left+right)/2;
	update(2*pos,left,mid,i,j,val);
	update(2*pos+1,mid+1,right,i,j,val);
	arvore[pos] = min(arvore[2*pos],arvore[2*pos+1]);
}
ll query(ll pos,ll left,ll right,ll i,ll j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return NULO;
	if(left >= i && right <= j){
		return arvore[pos];
	}
	ll mid = (left+right)/2;
	return min(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	ll n,q;
	scanf("%lld %lld",&n,&q);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&vetor[i]);
	}
	build(1,1,n);
	while(q--){
		ll a,b,c;
		scanf("%lld %lld %lld",&a,&b,&c);
		update(1,1,n,a,b,c);
		printf("%lld %lld\n",max(query(1,1,n,a,b),0LL),max(query(1,1,n,1,n),0LL));
	}
	return 0;
}