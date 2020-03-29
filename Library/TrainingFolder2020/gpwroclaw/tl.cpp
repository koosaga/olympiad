#include<stdio.h>
#include<algorithm>
#include<vector>
#define M 2000100
typedef long long ll;
ll n,x,y,z,i,a,b,j,f=2,v,res,dyn[M],zero=M/2;
std::vector<int> lis[M];
ll solve(int idx) {
	int i, sz=lis[idx].size();
	dyn[0] = dyn[1] = 0;
	for (i=2;i<=sz;i++) dyn[i] = std::min(z*(lis[idx][i-1]-lis[idx][i-2])-x-y+dyn[i-2],dyn[i-1]);
	return dyn[sz];
}
int main() {
	scanf("%lld%lld%lld%lld",&n,&x,&y,&z);
	for (i=0;i<n;i++) {
		scanf("%d%d",&a,&b);
		res += ((a<b)?x:y)*abs(b-a);
		v = (int)(a<b)*2-1;
		for (j=0;j<abs(b-a);j++) {
			if (f==v) zero+=v;
			lis[zero].push_back(i);
			f = v;
		}
	}
	for (i=0;i<M;i++) res += solve(i);
	printf("%lld\n",res);

	return 0;
}
