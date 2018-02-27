#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;
typedef long long lint;

pi p[MAXN];
int n, a[MAXN], x[MAXN];
int lst[MAXN][31];

int cnt(int s, int e, int v){
	if(s > e) return 0;
	return upper_bound(p, p + n +1, pi(v, e)) - 
	lower_bound(p, p + n+1, pi(v, s));
}

int main(){
freopen("hack.in", "r", stdin);
freopen("hack.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		x[i] = x[i-1] ^ a[i];
	}
	for(int i=0; i<=n; i++) p[i] = pi(x[i], i);
	sort(p, p + n + 1);
	fill(lst[n+1], lst[n+1] + 31, n+1);
	lint ans = 0;
	for(int i=n; i; i--){
		vector<int> v;
		for(int j=0; j<31; j++){
			if((a[i] >> j) & 1) lst[i][j] = lst[i+1][j];
			else lst[i][j] = i;
			v.push_back(lst[i][j]);
		}
		v.push_back(n + 1);
		sort(v.begin(), v.end());
		int cur = ~(1 << 31);
		int pos = i;
		for(int j=0; j<v.size(); j++){

			ans += cnt(pos, v[j] - 1, cur ^ x[i-1]);
			pos = v[j];
			cur &= a[pos];
		}
	}
	cout << ans << endl;
}
