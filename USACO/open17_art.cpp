#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;
 
int n, a[1005][1005];
int dx[1005][1005];
int sx[1000005], ex[1000005], sy[1000005], ey[1000005];
int chk[1000005];
 
int main(){
	scanf("%d",&n);
	memset(sx, 0x3f, sizeof(sx));
	memset(sy, 0x3f, sizeof(sy));
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			scanf("%d",&a[i][j]);
			sx[a[i][j]] = min(sx[a[i][j]], i);
			ex[a[i][j]] = max(ex[a[i][j]], i);
			sy[a[i][j]] = min(sy[a[i][j]], j);
			ey[a[i][j]] = max(ey[a[i][j]], j);
		}
	}
	int cnt = 0;
	for(int i=1; i<=n*n; i++){
		if(sx[i] <= ex[i] && sy[i] <= ey[i]){
			dx[sx[i]][sy[i]]++;
			dx[sx[i]][ey[i]+1]--;
			dx[ex[i]+1][sy[i]]--;
			dx[ex[i]+1][ey[i]+1]++;
			cnt++;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			dx[i][j] += dx[i-1][j] + dx[i][j-1] - dx[i-1][j-1];
			if(dx[i][j] > 1){
				chk[a[i][j]] = 1;
			}
		}
	}
	int ans = 0;
	for(int i=1; i<=n*n; i++){
		if(!chk[i]) ans++;
	}
	if(cnt == 1 && n > 1) ans--;
	cout << ans;
}
