#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
 
struct pnt{
	int x, y, w;
	bool operator<(const pnt &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
}a[MAXN];
 
int n;
 
int solve(int sx, int sy){
	int ans = 0;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			int pos = lower_bound(a, a+n, (pnt){sx + i, sy + j, -1}) - a;
			if(pos < n && sx + i == a[pos].x && sy + j == a[pos].y) ans += a[pos].w;
		}
	}
	return ans;
}
 
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].w);
	}
	sort(a, a+n);
	int ans = 0;
	for(int i=0; i<n; i++){
		for(int j=-1; j<=0; j++){
			for(int k=-1; k<=0; k++){
				ans = max(ans, solve(a[i].x + j, a[i].y + k));
			}
		}
	}
	printf("%d / 1\n", ans);
}
