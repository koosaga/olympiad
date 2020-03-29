#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 4000005;

typedef long long ll;
ll n,x,y,z,i,a,b,j,f=2,v,res,dyn[2 * MAXN],zero;
std::vector<int> lis[2 * MAXN];

void init(){
	n=x=y=z=i=a=b=j=v=res=0; // fuck you tlwpdus
	f = 2;
	zero = MAXN;
	for(int i=0; i<2*MAXN; i++) lis[i].clear();
}
ll solve(int idx) {
	int i, sz=lis[idx].size();
	dyn[0] = dyn[1] = 0;
	for (i=2;i<=sz;i++) dyn[i] = std::min(z*(lis[idx][i-1]-lis[idx][i-2])-x-y+dyn[i-2],dyn[i-1]);
	return dyn[sz];
}

char str[MAXN];

void solve(){
	init();
	scanf("%lld %lld %lld %lld",&n,&x,&y,&z);
	n *= 4;
	vector<int> aa(n), bb(n);
	scanf("%s", str);
	for(int i=0; i<n/4; i++){
		int msk = 0;
		if(str[i] >= '0' && str[i] <= '9') msk = str[i] - '0';
		else msk = str[i] - 'A' + 10;
		for(int j=0; j<4; j++){
			if((msk >> j) & 1) aa[4*i+3-j] = 1;
		}
	}
	scanf("%s", str);
	for(int i=0; i<n/4; i++){
		int msk = 0;
		if(str[i] >= '0' && str[i] <= '9') msk = str[i] - '0';
		else msk = str[i] - 'A' + 10;
		for(int j=0; j<4; j++){
			if((msk >> j) & 1) bb[4*i+3-j] = 1;
		}
	}
	for (i=0;i<n;i++) {
		int a = aa[i];
		int b = bb[i];
		res += ((a<b)?x:y)*abs(b-a);
		v = (int)(a<b)*2-1;
		for (j=0;j<abs(b-a);j++) {
			if (f==v) zero+=v;
			lis[zero].push_back(i);
			f = v;
		}
	}
	for (i=0;i<MAXN*2;i++) res += solve(i);
	printf("%lld\n",res);
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--) solve();
}
