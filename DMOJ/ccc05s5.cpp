// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccc05s5
#include <cstdio>
typedef long long ll;
const ll MAXN = 1e9 + 10;
ll resp,n;
typedef struct node* pnode;
struct node{
	ll val;
	pnode l,r;
	node() : l(NULL),r(NULL),val(0){}
	void update(ll left,ll right,ll x,ll delta){
		if(left == right){
			val += delta;
			return;
		}
		ll mid = (left+right)/2;
		val += delta;
		if(x <= mid){
			if(l == NULL) l = new node;
			l->update(left,mid,x,delta);
		}
		else{
			if(r == NULL) r = new node;
			r->update(mid+1,right,x,delta);
		}
	}
	ll query(ll left,ll right,ll i,ll j){
		if(left>right||left>j||right<i) return 0;
		if(left >= i && right <= j){
			return val;
		}
		ll mid = (left+right)/2;
		ll sinistra = (l == NULL) ? 0 : l->query(left,mid,i,j);
		ll destra = (r == NULL) ? 0 : r->query(mid+1,right,i,j);
		return sinistra + destra;
	}
};
int main(){
	scanf("%lld",&n);
	pnode raiz = new node;
	for(ll i=1;i<=n;i++){
		ll davez;
		scanf("%lld",&davez);
		davez++;
		//printf("%lld of %lld\n",1LL + raiz->query(1,MAXN,davez+1,MAXN),i);
		resp += 1LL + raiz->query(1,MAXN,davez+1,MAXN);
		raiz->update(1,MAXN,davez,1);
	}
	printf("%.2lf\n",(double)resp/(double)n);
	return 0;
}