// Ivan Carvalho
// Solution to https://dmoj.ca/problem/acc3p4
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

ll seg[4*MAXN],lazy_a[4*MAXN],lazy_r[4*MAXN];
int N,Q;

ll soma_pa(ll a,ll r,ll n){
	ll b = a + (n-1)*r;
	return ((a+b)*n)/2;
}

void propagate(int pos,int left,int right){

	if(lazy_a[pos] == 0 && lazy_r[pos] == 0) return;

	seg[pos] += soma_pa(lazy_a[pos],lazy_r[pos],right - left + 1);

	if(left != right){
		int mid = (left+right)/2;
		lazy_a[2*pos] += lazy_a[pos];
		lazy_a[2*pos+1] += lazy_a[pos] + 
(mid+1-left)*lazy_r[pos];
		lazy_r[2*pos] += lazy_r[pos];
		lazy_r[2*pos+1] += lazy_r[pos];
	}

	lazy_a[pos] = 0;
	lazy_r[pos] = 0;

}

void update(int pos,int left,int right,int i,int j,ll a,ll r){

	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;

	if(left >= i && right <= j){
		lazy_a[pos] += a + r*(left - i);
		lazy_r[pos] += r;
		propagate(pos,left,right);
		return;
	}

	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,a,r);
	update(2*pos+1,mid+1,right,i,j,a,r);

	seg[pos] = seg[2*pos] + seg[2*pos+1];

}

ll query(int pos,int left,int right,int i,int j){
	
	propagate(pos,left,right);
	
	if(left >= i && right <= j) return seg[pos];

	int mid = (left+right)/2;
	if(j <= mid) return query(2*pos,left,mid,i,j);
	else if(i >= mid + 1) return query(2*pos+1,mid+1,right,i,j);
	else return query(2*pos,left,mid,i,j) + 
query(2*pos+1,mid+1,right,i,j);

}

int main(){

	scanf("%d %d",&N,&Q);

	for(int q = 1;q<=Q;q++){
		int op,i,j,k;
		scanf("%d",&op);
		if(op == 1){
			scanf("%d %d %d",&i,&j,&k);
			update(1,1,N,i,j,k,k);
		}
		else{
			scanf("%d %d",&i,&j);
			printf("%lld\n",query(1,1,N,i,j));
		}
	}

	return 0;

}
