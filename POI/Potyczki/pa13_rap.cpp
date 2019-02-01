#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int MAXN = 500005;
 
lint a[MAXN], b[MAXN];
int n, k;
 
pi solve(lint x){
	priority_queue<lint, vector<lint>, greater<lint> > pq1;
	priority_queue<lint> pq2;
	lint ans = 0;
	int cnt = 0;
	for(int i=1; i<=n; i++){
		pq1.push(a[i] - x);
		lint cost1 = (pq2.empty() ? 1e18 : (b[i] - pq2.top()));
		lint cost2 = (pq1.empty() ? 1e18 : (pq1.top() + b[i]));
		if(cost1 >= 0 && cost2 >= 0){
			continue;
		}
		if(cost1 <= cost2){
			pq2.pop();
			pq2.push(b[i]);
			ans += cost1;
		}
		else{
			pq1.pop();
			pq2.push(b[i]);
			ans += cost2; 
			cnt++;
		}
	}
	return make_pair(ans, cnt);
}
 
int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1; i<=n; i++){
		scanf("%lld",&b[i]);
	}
	lint s = 0, e = 2e9;
	while(s != e){
		lint m = (s+e+1)/2;
		if(solve(m).second > k) e = m-1;
		else s = m;
	}
	cout << solve(s).first + s * k;
}