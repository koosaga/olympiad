#include <bits/stdc++.h>
using namespace std; 
const int MAXN = 1005;

vector<int> arr[505];
int n, a[MAXN];
int dp[140000];

int solve(vector<int> x){
	n = x.size();
	fill(dp, dp + 140000, -1e9);
	dp[0] = 0;
	int sum = 0;
	for(int i=0; i<n; i++){
		for(int j=sum; j>=0; j--){
			if(j == 0 || (j & -j) >= (1 << x[i])){
				dp[j + (1<<x[i])] = max(dp[j + (1<<x[i])], dp[j] + 1);
			}
		}
		sum += (1 << x[i]);
		sum = min(sum, 1<<17);
	}
	int ans = 0;
	for(int i=0; i<18; i++) ans = max(ans, dp[1 << i]);
	return ans;
}

int main(){
	while(true){
		cin >> n;
		if(!n) break;
		for(int i=0; i<n; i++){
			int x;
			cin >> x;
			int pw = 0;
			while(x % 2 == 0) x >>= 1, pw++;
			arr[x].push_back(pw);
		}
		int ans = 0;
		for(int i=1; i<=500; i++){
			ans = max(ans, solve(arr[i]));
			arr[i].clear();
		}
		cout << ans << endl;
	}
}
