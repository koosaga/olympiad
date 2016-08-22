#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[1000005];
int dp[1000005];

int query(int k){
	deque<int> dq;
	dq.push_back(1);
	for(int i=2; i<=n; i++){
		while(!dq.empty() && dq.front() < i - k){
			dq.pop_front();
		}
		dp[i] = dp[dq.front()] + (a[dq.front()] <= a[i]);
		while(!dq.empty() && pi(dp[dq.back()], -a[dq.back()]) > pi(dp[i], -a[i])){
			dq.pop_back();
		}
		dq.push_back(i);
	}
	return dp[n];
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	int q;
	cin >> q;
	while(q--){
		int x;
		scanf("%d",&x);
		printf("%d\n", query(x));
	}
}

