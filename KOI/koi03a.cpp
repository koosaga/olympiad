#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n,piv;
int left[10005], right[10005], dom[10005];
int ll[10005], lr[10005];

void solve(int pos, int i){
	if(pos == -1) return;
	solve(left[pos],i+1);
	piv++;
	ll[i] = min(ll[i],piv);
	lr[i] = max(lr[i],piv);
	solve(right[pos],i+1);
}

int main(){
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		int p;
		scanf("%d",&p);
		scanf("%d %d",&left[p],&right[p]);
		dom[left[p]+1]++;
		dom[right[p]+1]++;
	}
	memset(ll,0x3f,sizeof(ll));
	for (int i=1; i<=n; i++) {
		if(!dom[i+1]){
			solve(i,0);
			break;
		}
	}
	for (int i=0; i<=n+1; i++) {
		lr[i] -= ll[i];
	}
	int *pt = max_element(lr,lr+2+n);
	printf("%d %d",(int)(pt-lr)+1,(*pt)+1);
}