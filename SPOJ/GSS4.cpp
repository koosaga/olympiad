// Ivan Carvalho
// Solution to https://www.spoj.com/problems/GSS4/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define MAXN 100001
using namespace std;
typedef long long ll;
ll full[4*MAXN],vetor[MAXN],st[4*MAXN];
void build(ll pos, ll left, ll right){
	if (left == right){
		st[pos] = vetor[left];
		full[pos] = (st[pos] == (right - left + 1));
		return;
	}
	ll mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	st[pos] = st[2*pos] + st[2*pos+1];
	full[pos] = (st[pos] == (right - left + 1));
}
void update(ll pos, ll left, ll right,ll i, ll j){
	if (left > right || left > j || right < i) return;
	if (left == right){
		st[pos] = ll(sqrt(st[pos]));
		full[pos] = (st[pos] == (right - left + 1));
		return;
	}
	ll mid = (left+right)/2;
	if (!full[2*pos]) update(2*pos,left,mid,i,j);
	if (!full[2*pos+1]) update(2*pos+1,mid+1,right,i,j);
	st[pos] = st[2*pos] + st[2*pos+1];
	full[pos] = (st[pos] == (right - left + 1));
}
ll query(ll pos, ll left, ll right, ll i, ll j){
	if (left > right || left > j || right < i) return 0;
	if (left >= i && right <= j){
		return st[pos];
	}
	ll mid = (left+right)/2;
	return query(2*pos,left,mid,i,j)+query(2*pos+1,mid+1,right,i,j);
}
int main(){
	ll caso=1,n,q;
	while(scanf("%lld",&n) != EOF){
		memset(full,0,sizeof(full));
		memset(st,0,sizeof(st));
		printf("Case #%lld:\n",caso++);
		for(ll i=1;i<=n;i++) scanf("%lld",&vetor[i]);
		//for(ll i=1;i<=n;i++) printf("%lld ",vetor[i]);
		//printf("\n");
		build(1,1,n);
		scanf("%lld",&q);
		while(q--){
			ll a,b,c;
			scanf("%lld %lld %lld",&a,&b,&c);
			if (b > c) swap(b,c);
			//printf("A %lld B %lld C %lld\n",a,b,c);
			if (a == 0){
				update(1,1,n,b,c);
			}
			if (a == 1){
				printf("%lld\n",query(1,1,n,b,c));
			}
		}
		printf("\n");
	}
	return 0;
}