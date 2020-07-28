// Ivan Carvalho
// Solution to https://www.spoj.com/problems/SEGSQRSS/
#include <cstdio>
#include <queue>
#define MAXN 100001
#define MP make_pair
#define DEFINE 0
#define ADD 1
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
ll arvore[4*MAXN],vetor[MAXN],n,q;
queue<ii> lazy[4*MAXN];
void build(ll pos, ll left, ll right){
	while(!lazy[pos].empty()){
		lazy[pos].pop();
	}
	if (left == right){
		arvore[pos] = vetor[left] * vetor[left];
		return;
	}
	int mid = (left+right)/2;
	build(2*pos,left,mid);
	build(2*pos+1,mid+1,right);
	arvore[pos] = arvore[2*pos] + arvore[2*pos+1];
}
void update_define(ll pos, ll left, ll right, ll i, ll j, ll val){
	 while(!lazy[pos].empty()){
	 	ii davez = lazy[pos].front();
	 	lazy[pos].pop();
	 	if (davez.first == DEFINE){
	 		arvore[pos] = (right - left + 1) * davez.second * davez.second;
	 	}
	 	if (davez.first == ADD){
	 		arvore[pos] += (right - left + 1) * davez.second * davez.second;
	 	}
	 	if (left != right){
	 		lazy[2*pos].push(davez);
	 		lazy[2*pos+1].push(davez);
	 	}
	 }
	if (left > right || left > j || right < i) return;
	if (left >= i && right <= j){
		arvore[pos] = (right - left + 1) * val * val;
		if (left != right){
			lazy[2*pos].push(MP(DEFINE,val));
			lazy[2*pos+1].push(MP(DEFINE,val));
		}
		return ;
	}
	int mid = (left+right)/2;
	update_define(2*pos,left,mid,i,j,val);
	update_define(2*pos+1,mid+1,right,i,j,val);
	arvore[pos] = arvore[2*pos] + arvore[2*pos+1];
}
void update_add(ll pos, ll left, ll right, ll i, ll j, ll val){
	 while(!lazy[pos].empty()){
	 	ii davez = lazy[pos].front();
	 	lazy[pos].pop();
	 	if (davez.first == DEFINE){
	 		arvore[pos] = (right - left + 1) * davez.second * davez.second;
	 	}
	 	if (davez.first == ADD){
	 		arvore[pos] += (right - left + 1) * davez.second * davez.second;
	 	}
	 	if (left != right){
	 		lazy[2*pos].push(davez);
	 		lazy[2*pos+1].push(davez);
	 	}
	 }
	if (left > right || left > j || right < i) return;
	if (left >= i && right <= j){
		arvore[pos] += (right - left + 1) * val * val;
		if (left != right){
			lazy[2*pos].push(MP(ADD,val));
			lazy[2*pos+1].push(MP(ADD,val));
		}
		return ;
	}
	int mid = (left+right)/2;
	update_add(2*pos,left,mid,i,j,val);
	update_add(2*pos+1,mid+1,right,i,j,val);
	arvore[pos] = arvore[2*pos] + arvore[2*pos+1];
}
ll query(ll pos, ll left, ll right, ll i, ll j){
	 while(!lazy[pos].empty()){
	 	ii davez = lazy[pos].front();
	 	lazy[pos].pop();
	 	if (davez.first == DEFINE){
	 		arvore[pos] = (right - left + 1) * davez.second * davez.second;
	 	}
	 	if (davez.first == ADD){
	 		arvore[pos] += (right - left + 1) * davez.second * davez.second;
	 	}
	 	if (left != right){
	 		lazy[2*pos].push(davez);
	 		lazy[2*pos+1].push(davez);
	 	}
	 }
	if (left > right || left > j || right < i) return 0;
	if (left >= i && right <= j){
		return arvore[pos];
	}
	int mid = (left+right)/2;
	return query(2*pos,left,mid,i,j) + query(2*pos+1,mid+1,right,i,j);
}
int main(){
	ll TC;
	scanf("%lld",&TC);
	for(ll fool = 1;fool <= TC;fool++){
		printf("Case %lld:\n",fool);
		scanf("%lld %lld",&n,&q);
		for(int i=1;i<=n;i++) scanf("%lld",&vetor[i]);
		build(1,1,n);
		while(q--){
			ll op;
			scanf("%lld",&op);
			if (op == 0){
				ll a,b,c;
				scanf("%lld %lld %lld",&a,&b,&c);
				update_define(1,1,n,a,b,c);
			}
			if (op == 1){
				ll a,b,c;
				scanf("%lld %lld %lld",&a,&b,&c);
				update_add(1,1,n,a,b,c);
			}
			if (op == 2){
				ll a,b;
				scanf("%lld %lld",&a,&b);
				printf("%lld\n",query(1,1,n,a,b));
			}
		}
	}
	return 0;
}