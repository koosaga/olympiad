// Ivan Carvalho
// Solution to https://www.spoj.com/problems/RPLN/
#include <cstdio>
#include <algorithm>
#define MAXN 100001
#define NULLV 1000000001
#define LEFT(S) ((S<<1)+1)
#define RIGHT(S) ((S<<1)+2)
#define MID(R,S) ((R+S)>>1)
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    int neg = 0;
    for(;((c<48 || c>57) && c != '-');c = gc());
    if(c=='-') {neg=1;c=gc();}
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
    if(neg) x=-x;
}
using namespace std;
int st[4*MAXN],A[MAXN];
void build(int pos, int left, int right){
	if (left == right){
		st[pos] = A[left];
		return;
	}
	int mid = MID(left,right);
	build(LEFT(pos),left,mid);
	build(RIGHT(pos),mid+1,right);
	st[pos] = min(st[LEFT(pos)],st[RIGHT(pos)]);
}
int rmq(int pos,int left, int right, int i, int j){
	if (right < i || left > j) return NULLV;
	if (left >= i && right <= j){
		return st[pos];
	} 
	int mid = MID(left,right);
	int p1 = rmq(LEFT(pos),left,mid,i,j);
	int p2 = rmq(RIGHT(pos),mid+1,right,i,j);
	return min(p1,p2);
}
int main(){
	int scenario;
	getint(scenario);
	for(int sce = 1;sce<=scenario;sce++){
		printf("Scenario #%d:\n",sce);
		int n,q;
		getint(n);
		getint(q);
		for(int i=0;i<n;i++) getint(A[i]);
		build(0,0,n-1);
		while(q--){
			int x,y;
			getint(x);
			getint(y);
			x--;
			y--;
			printf("%d\n",rmq(0,0,n-1,x,y));
		}
	}
	return 0;
} 