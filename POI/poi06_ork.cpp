#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, k, a[2005][2005];
lint s[2005][2005];

lint sum(int sx, int ex, int sy, int ey){
	return s[ex][ey] - s[sx-1][ey] - s[ex][sy-1] + s[sx-1][sy-1];
}

bool vis[2005][2005];
struct rect{
	int sx, ex, sy, ey;
};

int solve(){
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			s[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + a[i][j];
		}
	}
	queue<rect> que;
	que.push({1, n, 1, m});
	int ans = -1;
	memset(vis, 0, sizeof(vis));
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		while(x.sx <= x.ex && sum(x.sx, x.sx, x.sy, x.ey) <= k) x.sx++;
		while(x.sx <= x.ex && sum(x.ex, x.ex, x.sy, x.ey) <= k) x.ex--;
		if(vis[x.sy][x.ey]) continue;
		vis[x.sy][x.ey] = 1;
		if(x.sx > x.ex){
			ans = max(ans, x.ey - x.sy + 1);
			continue;
		}
		if(x.sy != x.ey){
			if(sum(x.sx, x.ex, x.sy, x.sy) <= k) que.push({x.sx, x.ex, x.sy + 1, x.ey});
			if(sum(x.sx, x.ex, x.ey, x.ey) <= k) que.push({x.sx, x.ex, x.sy, x.ey - 1});
		}
	}
	return n + m - ans;
}

int main(){
	scanf("%d %d %d",&k,&m,&n);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	int ans = solve();
	swap(n, m);
	for(int i=1; i<=max(n, m); i++){
		for(int j=1; j<i; j++) swap(a[i][j], a[j][i]);
	}
	ans = min(ans, solve());
	cout << ans;
}
