// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1500
#include <cstdio>
#include <cstring>
#define MAXN 270030
long long st[MAXN],lazy[MAXN];
long long query(long long pos, long long left, long long right,long long i, long long j){
	if (left > right || left > j || right < i) return 0;
	if (lazy[pos] != 0){
		st[pos] += (right - left + 1) * lazy[pos];
		if (left != right){
			lazy[2*pos+1] += lazy[pos];
			lazy[2*pos+2] += lazy[pos];
		}
		lazy[pos] = 0;
	}
	if (left >= i && right <= j) return st[pos];
	long long mid = (left+right)/2;
	long long p1 = query(2*pos+1,left,mid,i,j);
	long long p2 = query(2*pos+2,mid+1,right,i,j);
	return p1 + p2;
}
void update(long long pos,long long left, long long right,long long i,long long j,long long val){
	if (lazy[pos]!=0){
		st[pos] += (right-left+1)*lazy[pos];
		if (left != right){
			lazy[2*pos+1] += lazy[pos];
			lazy[2*pos+2] += lazy[pos];
		}
		lazy[pos] = 0;
	}
	if (left > right || left > j || right < i) return;
	if(left >= i && right <= j){
		st[pos] += (right-left+1)*val;
		if (left != right){
			lazy[2*pos+1] += val;
			lazy[2*pos+2] += val;
		}
		return;
	}
	long long mid = (left+right)/2;
	update(2*pos+1,left,mid,i,j,val);
	update(2*pos+2,mid+1,right,i,j,val);
	st[pos] = st[2*pos+1] + st[2*pos+2];
}
int main(){
	long long casos;
	scanf("%lld",&casos);
	while(casos--){
		memset(st,0,sizeof(st));
		memset(lazy,0,sizeof(lazy));
		long long n,q;
		scanf("%lld %lld",&n,&q);
		while(q--){
			long long op;
			scanf("%lld",&op);
			if (op == 0){
				long long x,y,z;
				scanf("%lld %lld %lld",&x,&y,&z);
				x--;
				y--;
				update(0,0,n-1,x,y,z);
			}
			else{
				long long x,y;
				scanf("%lld %lld",&x,&y);
				x--;
				y--;
				printf("%lld\n",query(0,0,n-1,x,y));
			}
		}
	}
	return 0;
}
