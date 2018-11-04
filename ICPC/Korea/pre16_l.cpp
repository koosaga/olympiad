#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, lint> pi;

int n, w, l, a[1005];
int dp[1005];

int main(){
	cin >> n >> w >> l;
	for(int i=1; i<=n; i++) cin >> a[i];
	deque<int> dq;
	for(int i=0; i<w; i++) dq.push_back(0);
	int sum = 0, ret = 0, pnt = 1;
	while(pnt <= n){
		sum -= dq.front();
		dq.pop_front();
		if(a[pnt] + sum <= l){
			dq.push_back(a[pnt]);
			sum += a[pnt];
			pnt++;
		}
		else{
			dq.push_back(0);
		}
		ret++;
	}
	cout << ret + w;
}
