#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
typedef long long lint;

int n, m;
char a[MAXN][MAXN];
int s[MAXN][MAXN];
int up[MAXN][MAXN];

int sum(int sx, int ex, int sy, int ey){
	return s[ex][ey] - s[sx-1][ey] - s[ex][sy-1] + s[sx-1][sy-1];
}

int d[2][MAXN];
int e[2][MAXN];

int conquer(int s, int l, int r, int e){
	int curmin1 = 1e9;
	int curmin2 = 1e9;
	int ans = 0;
	while(s <= l && r <= e){
		if(min(curmin1, d[0][l]) < min(curmin2, d[1][r])){
			curmin2 = min(curmin2, d[1][r++]);
		}
		else{
			curmin1 = min(curmin1, d[0][l--]);
		}
		ans = max(ans, min(curmin1, curmin2) * (r - l - 1));
	}
	while(s <= l){
		curmin1 = min(curmin1, d[0][l--]);
		ans = max(ans, min(curmin1, curmin2) * (r - l - 1));
	}
	while(r <= e){
		curmin2 = min(curmin2, d[1][r++]);
		ans = max(ans, min(curmin1, curmin2) * (r - l - 1));
	}
	return ans;
}

int solve(int s, int e){
	if(s == e){
		int p = 0;
		int ret = 0;
		for(int i=1; i<=n; i++){
			while(sum(p+1, i, s, s) >= 2) p++;
			ret = max(ret, i - p);
		}
		return ret;
	}
	int m = (s+e)/2;
	int f[2][MAXN] = {};
	int ret = 0;
	for(int i=1; i<=n; i++){
		for(int j=m; j>=s; j--){
			while(sum(f[1][j] + 1, i, j, m) >= 2) f[1][j]++;
			while(sum(f[0][j] + 1, i, j, m) >= 1) f[0][j]++;
			d[0][j] = i - f[0][j];
			d[1][j] = i - f[1][j];
		}
		for(int j=m+1; j<=e; j++){
			while(sum(f[1][j] + 1, i, m+1, j) >= 2) f[1][j]++;
			while(sum(f[0][j] + 1, i, m+1, j) >= 1) f[0][j]++;
			d[0][j] = i - f[0][j];
			d[1][j] = i - f[1][j];
		}
		ret = max(ret, conquer(s, m, m+1, e));
		for(int i=s; i<=e; i++) swap(d[0][i], d[1][i]);
		ret = max(ret, conquer(s, m, m+1, e));
	}
	ret = max({ret, solve(s, m), solve(m+1, e)});
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%s", a[i] + 1);
		for(int j=1; j<=m; j++){
			if(a[i][j] == '#'){
				s[i][j]++;
				up[i][j] = i;
			}
			else up[i][j] = up[i-1][j];
			s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
		}
	}
	cout << solve(1, m) <<endl;
}

