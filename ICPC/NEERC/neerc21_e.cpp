#include<bits/stdc++.h>
using namespace std;
 
const int N = 100005;
 
int l, n, a[N], dmn[N], dmx[N], tr[N];
 
bool can (int L, int R, bool TRK = false)
{
	dmn[0] = dmx[0] = 0;
	for(int i=1;i<=n;i++) {
		dmn[i] = max(a[i], dmn[i-1] + L);
		dmx[i] = min(a[i+1], dmx[i-1] + R);
		if(dmn[i] > dmx[i]) return false;
	}
	if(dmx[n] != l) return false;
	if(TRK) {
		tr[n+1] = l;
		for(int i=n;i>1;i--) {
			tr[i] = min(tr[i+1] - L, dmx[i-1]);
		}
		tr[1] = 0;
		for(int i=1;i<=n;i++) {
			printf("%d %d\n", tr[i], tr[i + 1]);
		}
	}
	return true;
}
 
int main()
{
	scanf("%d%d",&l,&n);
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);
	}
	a[n+1] = l;
	int S = 0, E = l;
	while(S < E) {
		int M = (S+E)/2 + 1;
		can(M, l) ? S = M : E = M-1;
	}
	int L = S;
	S = L, E = l;
	while(S < E) {
		int M = (S+E)/2;
		can(L, M) ? E = M : S = M+1;
	}
	int R = S;
	can(L, R, true);
}
