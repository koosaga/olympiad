#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 505;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
const int nxt[6][4] = {
	{-1, -1, 1, 0},
	{1, -1, -1, 2},
	{-1, 0, 3, -1},
	{3, 2, -1, -1},
	{-1, 1, -1, 3},
	{0, -1, 2, -1}};

int n, k;
int a[MAXN][MAXN];

bool good(int x, int y){
	return 1<=x&&x<=n&&1<=y&&y<=n;
}

int sim(){
	int ret = 0;
	int px = 1, py = 1, ent = 0;
	while(good(px, py)){
		ret++;
		ent = nxt[a[px][py]][ent];
		if(ent < 0){
			return 1e9;
		}
		px += dx[ent];
		py += dy[ent];
	}
	if(px == n && py == n + 1&& ent == 0){
		return ret;
	}
	return 1e9;
}
int main(){
	cin >> n >> k;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			cin >> a[i][j];
		}
	}
	int ans = 1e9;
	if(k == 0){
		ans = sim();
	}
	else{
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				int x = a[i][j];
				for(int k=0; k<6; k++){
					if(x != k){
						a[i][j] = k;
						ans = min(ans, sim());
					}
				}
				a[i][j] = x;
			}
		}
	}
	if(ans > 6969) ans = -1;
	cout << ans << endl;
}
