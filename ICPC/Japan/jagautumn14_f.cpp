#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
const int MAXN = 4005;
typedef pair<int, int> pi;

int n;
vector<pi> l, r;
lint dp[MAXN][MAXN];
lint tmp[MAXN];

int main(){
	while(true){
		l.clear();
		r.clear();
	cin >> n;
	if(n == 0)  break;
	if(n == 2){
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		cout << abs(a - c) << endl;
		continue;
	}
	for(int i=0; i<n; i++){
		int x, y;
		cin >> x >> y;
		if(y == 1) l.push_back(pi(x, 1));
		else r.push_back(pi(x, y));
	}
	sort(l.begin(), l.end());
	sort(r.begin(), r.end());
	if(r.empty()){
		cout << -1 << endl;
		continue;
	}
	if(r.size() >= 2){
		r[0].second--;
		for(int i=1; i+1<r.size(); i++) r[i].second -= 2;
		r.back().second--;
	}
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	for(int i=1; i<=r.size(); i++){
		for(int j=0; j<l.size(); j++) tmp[j+1] = tmp[j] + abs(r[i-1].first - l[j].first);
		priority_queue<pair<lint, int> , vector<pair<lint, int>> , greater<pair<lint, int>> > pq;
		for(int j=0; j<=l.size(); j++){
			pq.push(make_pair(dp[i-1][j] - tmp[j], j));
			while(!pq.empty() && j - pq.top().second > r[i-1].second) pq.pop();
			dp[i][j] = pq.top().first + tmp[j];
		}
	}
	lint ans = dp[r.size()][l.size()] + r.back().first - r[0].first;
	if(ans > 1e17) ans = -1;
	cout << ans << endl;
	}
}
