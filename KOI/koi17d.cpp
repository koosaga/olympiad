#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1505;
char buf[5];

int n, a[MAXN][MAXN];
lint dp[MAXN][MAXN], sum;

struct bit{
	int tree[2*MAXN];
	void add(int x, int v){
		while(x <= 2 * n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit[2*MAXN];

void update(int s, int l, int r, int v){
	bit[s].add(l, v);
	bit[s].add(r+1, -v);
	sum += (r - l + 1) * v;
}

bool ok(int x, int y){
	return x >= 1 && x <= n && y >= 1 && y <= n;
}

int get(int x, int y){
	return dp[x][y] + bit[x+y].query(y);
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		dp[0][i] = dp[i][0] = -1e10;
		for(int j=1; j<=n; j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i == j && j == 1) dp[i][j] = a[i][j];
			else{
				pi l(dp[i-1][j] + a[i][j], 1);
				pi r(dp[i][j-1] + a[i][j], 2);
				dp[i][j] = max(l, r).first;
			}
			sum += dp[i][j];
		}
	}
	printf("%lld\n", sum);
	for(int q=1; q<=n; q++){
		scanf("%s", buf);
		int x, y; scanf("%d %d",&x,&y);
		int v = (*buf == 'U' ? 1 : -1);
		a[x][y] += v;
		update(x+y, y, y, v);
		int l = y, r = y;
		for(int i=x+y+1; i<=n+n; i++){
			if(!ok(i-l, l)) l++;
			else{
				pi le = pi(get(i-l, l-1) + a[i-l][l], 1);
				pi ri = pi(get(i-l-1, l) + a[i-l][l], 2);
				if(max(le, ri).first == get(i-l, l)) l++;
			}
			r++;
			if(!ok(i-r, r)) r--;
			else{
				pi le = pi(get(i-r, r-1) + a[i-r][r], 1);
				pi ri = pi(get(i-r-1, r) + a[i-r][r], 2);
				if(max(le, ri).first == get(i-r, r)) r--;
			}
			update(i, l, r, v);
			if(l > r) break;
		}
		printf("%lld\n", sum);
	}
}
