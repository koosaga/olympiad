#include <cstdio>
#include <algorithm>
#include <cstdlib>
int n,q,a[20],dp[21][21];

int f(int xp, int yp, int pos){
	if(pos==q) return 0;
	return std::min(f(xp,a[pos],pos+1)+abs(yp-a[pos]),f(yp,a[pos],pos+1)+abs(xp-a[pos]));
}

int main(){
	int d1,d2;
	scanf("%d %d %d %d",&n,&d1,&d2,&q);
	for (int i=0; i<q; i++) scanf("%d",&a[i]);
	printf("%d",f(d1,d2,0));
}