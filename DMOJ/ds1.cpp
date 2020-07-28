// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ds1
#include <cstdio>
#include <vector>
#include <algorithm>
#define MAXN 100100
#define LSOne(S) (S & (-S))
using namespace std;
typedef long long ll;
ll vetor[MAXN],n,m;
struct bit{
	vector<ll> ft;
	ll tam;
	bit(ll tam) : tam(tam) {ft.assign(tam+1,0);}
	void update(ll pos,ll val){
		while(pos<=tam){
			ft[pos]+=val;
			pos += LSOne(pos);
		}
	}
	ll read(ll pos){
		ll ans = 0;
		while(pos > 0){
			ans += ft[pos];
			pos -= LSOne(pos);
		}
		return ans;
	}
	ll query(ll a,ll b){
		return read(b) - read(a-1);
	}
};
int main(){
	scanf("%lld %lld",&n,&m);
	bit A(n);
	bit B(MAXN);
	for(ll i=1;i<=n;i++){
		scanf("%lld",&vetor[i]);
		A.update(i,vetor[i]);
		B.update(vetor[i],1);
	}
	while(m--){
		char op;
		scanf(" %c",&op);
		if(op == 'C'){
			ll i,v;
			scanf("%lld %lld",&i,&v);
			A.update(i,-vetor[i]);
			B.update(vetor[i],-1);
			vetor[i] = v;
			A.update(i,vetor[i]);
			B.update(vetor[i],1);
		}
		else if(op == 'S'){
			ll l,r;
			scanf("%lld %lld",&l,&r);
			printf("%lld\n",A.query(l,r));
		}
		else{
			ll v;
			scanf("%lld",&v);
			printf("%lld\n",B.query(1,v));
		}
	}
	return 0;
}
}