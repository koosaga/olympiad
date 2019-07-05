#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using lint = long long;
using pi = pair<lint, lint>;

int n, m;
int a[MAXN][MAXN];

vector<pi> frac;
vector<int> who;

pi howLeft[MAXN][MAXN];
bool vis[MAXN];

auto cmp = [](pi a, pi b){
	return (__int128)a.first * b.second < (__int128) b.first * a.second;
};

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1; i<=n; i++){
		lint sum = 0;
		for(int j=1; j<=m; j++){
			sum += a[i][j];
		}
		lint curSum = 0;
		howLeft[i][0] = pi(0, 1);
		int ptr = 0;
		for(int j=1; j<n; j++){
			while(curSum + a[i][ptr+1] * n<= sum * j){
				curSum += a[i][++ptr] * n;
			}
			lint tmp = sum * j - curSum;
			auto frac = pi(tmp, a[i][ptr + 1] * n);
			frac.first += 1ll * ptr * n * a[i][ptr + 1];
			howLeft[i][j] = frac;
		}
		howLeft[i][n] = pi(m, 1);
	}
	for(int i=1; i<=n; i++){
		pi minv(m + 1, 1);
		int pos = 1;
		for(int j=1; j<=n; j++){
			if(!vis[j] && cmp(howLeft[j][i], minv)){
				minv = howLeft[j][i];
				pos = j;
			}
		}
		vis[pos] = 1;
		who.push_back(pos);
		if(i < n) frac.push_back(minv);
	}
	for(auto &i : frac) printf("%lld %lld\n", i.first, i.second);
	for(auto &i : who) printf("%d ", i);
}
