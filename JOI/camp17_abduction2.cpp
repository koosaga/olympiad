#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
 
struct line{
	int pos, val, axis;
	bool operator<(const line &l)const{
		return val < l.val;
	}
}a[100005];
 
int n, m, q;
int st[100005], ed[100005];
lint ldp[100005], rdp[100005];
int rev[2][50005];
 
lint solve(int x, int y, int cs){
	memset(ldp, 0, sizeof(ldp));
	memset(rdp, 0, sizeof(rdp));
	int xl = 0, xh = n-1, yl = 0, yh = m-1;
	lint ret = 0;
	for(int i=0; i<n+m; i++){
		if(a[i].axis == 0){
			st[i] = yl, ed[i] = yh;
			if(rev[1][ed[i]] < i){
				int r = rev[1][ed[i]];
				rdp[i] = max(ldp[r] + abs(st[r] - a[i].pos), rdp[r] + abs(ed[r] - a[i].pos));
			}
			if(rev[1][st[i]] < i){
				int r = rev[1][st[i]];
				ldp[i] = max(ldp[r] + abs(st[r] - a[i].pos), rdp[r] + abs(ed[r] - a[i].pos));
			}
			if(cs & 1){
				if(x <= a[i].pos) xh = min(xh, a[i].pos);
				else xl = max(xl, a[i].pos);
			}
			else{
				if(x < a[i].pos) xh = min(xh, a[i].pos);
				else xl = max(xl, a[i].pos);
			}
		}
		else{
			st[i] = xl, ed[i] = xh;
			if(rev[0][ed[i]] < i){
				int r = rev[0][ed[i]];
				rdp[i] = max(ldp[r] + abs(st[r] - a[i].pos), rdp[r] + abs(ed[r] - a[i].pos));
			}
			if(rev[0][st[i]] < i){
				int r = rev[0][st[i]];
				ldp[i] = max(ldp[r] + abs(st[r] - a[i].pos), rdp[r] + abs(ed[r] - a[i].pos));
			}
			if(cs & 2){
				if(y <= a[i].pos) yh = min(yh, a[i].pos);
				else yl = max(yl, a[i].pos);
			}
			else{
				if(y < a[i].pos) yh = min(yh, a[i].pos);
				else yl = max(yl, a[i].pos);
			}
		}
		if(a[i].axis == 0 && a[i].pos == x){
			ret = max({ret, ldp[i] + abs(st[i] - y), rdp[i] + abs(ed[i] - y)});
		}
		if(a[i].axis == 1 && a[i].pos == y){
			ret = max({ret, ldp[i] + abs(st[i] - x), rdp[i] + abs(ed[i] - x)});
		}
	}
	return ret;
}
 
int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i].val);
		a[i].pos = i;
		a[i].axis = 0;
	}
	for(int i=0; i<m; i++){
		scanf("%d",&a[i+n].val);
		a[i+n].pos = i;
		a[i+n].axis = 1;
	}
	sort(a, a+n+m);
	reverse(a, a+n+m);
	for(int i=0; i<n+m; i++){
		rev[a[i].axis][a[i].pos] = i;
	}
	for(int i=0; i<q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		lint ret = 0;
		for(int j=0; j<4; j++) ret = max(ret, solve(x-1, y-1, j));
		printf("%lld\n", ret);
	}
}
