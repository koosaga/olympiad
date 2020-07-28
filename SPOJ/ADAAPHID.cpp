// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAAPHID/
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const ll ini = 0;
const ll fim = (1LL << 60);
vector<ll> esq,dir,val;
ll it,n,last;
void update(ll pos,ll left,ll right,ll x,ll delta){
	val[pos] += delta;
	if(left == right) return;
	ll mid = (left+right)/2;
	if(x <= mid){
		if(esq[pos] == -1){
			esq[pos] = ++it;
			esq.push_back(-1);
			dir.push_back(-1);
			val.push_back(0);
		}
		update(esq[pos],left,mid,x,delta);
	}
	else{
		if(dir[pos] == -1){
			dir[pos] = ++it;
			esq.push_back(-1);
			dir.push_back(-1);
			val.push_back(0);
		}
		update(dir[pos],mid+1,right,x,delta);
	}
}
ll query(ll pos,ll left,ll right,ll i,ll j){
	if(left > right || left > j || right < i) return 0;
	if(left >= i && right <= j){
		return val[pos];
	}
	ll mid = (left+right)/2;
	ll sinistra = (esq[pos] == -1) ? 0 : query(esq[pos],left,mid,i,j);
	ll destra = (dir[pos] == -1) ? 0 : query(dir[pos],mid+1,right,i,j);
	return sinistra + destra;
}
int main(){
	esq.push_back(-1);
	dir.push_back(-1);
	val.push_back(0);
	scanf("%lld",&n);
	while(n--){
		ll x,y;
		scanf("%lld %lld",&x,&y);
		x ^= last;
		y ^= last;
		update(0,ini,fim,x,y);
		last = query(0,0,fim,0,x);
		printf("%lld %lld\n",x,last);
	}
	return 0;
}