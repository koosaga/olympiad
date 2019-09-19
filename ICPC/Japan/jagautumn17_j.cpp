#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 200005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

int n;
lint d[MAXN], g[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=2; i<=n; i++) scanf("%lld",&d[i]);
	for(int i=1; i<=n; i++) scanf("%lld",&g[i]);
	priority_queue<lint, vector<lint>, greater<lint>> L, R;
	lint offL = 0, offR = 0;
	lint ans = accumulate(g + 1, g + n + 1, 0ll);
	for(int i=1; i<=n; i++){
		if(i > 1){
			offL += d[i];
			offR += d[i];
		}
		L.push(-g[i] - offL);
		R.push(g[i] - offR);
		while(-(L.top() + offL) > (R.top() + offR)){
			auto t1 = -(L.top() + offL);
			auto t2 = R.top() + offR;
			ans -= t1 - t2;
			L.pop(); R.pop();
			R.push(t1 - offR);
			L.push(-t2 - offL);
		}
	}
	while(sz(R) && R.top() + offR < 0){
		ans += R.top() + offR;
		R.pop();
	}
	while(sz(L) && L.top() + offL > 0){
		ans -= L.top() + offL;
		L.pop();
	}
	cout << ans << endl;
}
