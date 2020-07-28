// Ivan Carvalho
// Solution to https://dmoj.ca/problem/mcco17p2
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2*1e5 + 10;
int N,K,Q;
ll seg[4*MAXN],lazy[4*MAXN];
void propagate(int pos,int left,int right){
	if(lazy[pos] == 0) return;
	seg[pos] += lazy[pos];
	if(left != right){
		lazy[2*pos] += lazy[pos];
		lazy[2*pos+1] += lazy[pos];
	}
	lazy[pos] = 0;
}
void update(int pos,int left,int right,int i,int j,ll delta){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return;
	if(left >= i && right <= j){
		lazy[pos] = delta;
		propagate(pos,left,right);
		return;
	}
	int mid = (left+right)/2;
	update(2*pos,left,mid,i,j,delta);
	update(2*pos+1,mid+1,right,i,j,delta);
	seg[pos] = max(seg[2*pos],seg[2*pos+1]);
}
ll query(int pos,int left,int right,int i,int j){
	propagate(pos,left,right);
	if(left>right||left>j||right<i) return 0;
	if(left >= i && right <= j){
		return seg[pos];
	}
	int mid = (left+right)/2;
	return max(query(2*pos,left,mid,i,j),query(2*pos+1,mid+1,right,i,j));
}
int main(){
	scanf("%d %d %d",&N,&K,&Q);
	while(Q--){
		int op;
		scanf("%d",&op);
		if(op == 0){
			int p;
			ll v;
			scanf("%d %lld",&p,&v);
			update(1,0,N-1,max(p - K + 1,0),p,v);
		}
		else if(op == 1){
			int l,r;
			scanf("%d %d",&l,&r);
			printf("%lld\n",query(1,0,N-1,l,r));
		}
	}
	return 0;
}