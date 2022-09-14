#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 3005;

int n, c;
int dp[MAXN][MAXN];

int solve_case1(vector<int> a){
	int ret = 0;
	for(int i = 1; i <= n; i++){
		int k = i;
		while(k - 1 > 0 && a[k - 1] >= a[k]) k--;
		vector<int> cnt(c + 1), sum(c + 1);
		priority_queue<int, vector<int>, greater<int>> pq;
		for(int j = k; j <= i; j++){
			cnt[a[j]]++;
			sum[a[j]]++;
			if(sum[a[j]] == 1) pq.push(a[j]);
		}
		for(int i = 1; i <= c; i++) sum[i] += sum[i - 1];
		int who_is_low = -1, aux = 0;
		int totMin = 1e9;
		for(int j = i + 1; j <= n; j++){
			if(a[j] < a[i]){
				if(who_is_low == -1){
					who_is_low = a[j];
				}
				else if(who_is_low != a[j]) break;
				aux++;
			}
			else{
				cnt[a[j]]--;
				if(cnt[a[j]] == -1) totMin = min(totMin, a[j]);
			}
			while(sz(pq) && cnt[pq.top()] <= 0) pq.pop();
			int w = totMin;
			if(sz(pq)) w = min(w, pq.top());
			if(w > c) ret = max(ret, j - k + 1 + 2 * dp[k - 1][j + 1]);
			else{
				int tot = sum[w] * 2 - 2 * max(cnt[w], 0) + aux;
				ret = max(ret, tot);
			}
		}
	}
	return ret;
}


int solve_case2(vector<int> a){
	int ret = 0;
	auto Do = [&](int j, int k){
		if(k == n + 1){
			ret = max(ret, k - j);
			return;
		}
		int z = k + 1;
		while(z <= n && a[z - 1] >= a[z]) z++;
		vector<int> cnt(c + 1);
		vector<int> sum(c + 1);
		priority_queue<int> pq;
		for(int j = k; j < z; j++){
			cnt[a[j]]++;
			sum[a[j]]++;
			if(sum[a[j]] == 1) pq.push(a[j]);
		}
		for(int i = 1; i <= c; i++) sum[i] += sum[i - 1];
		int plen = k - j;
		ret = max(ret, k - j);
		int curmax = 0;
		while(j > 1){
			j--;
			cnt[a[j]]--;
			if(cnt[a[j]] == -1) curmax = max(curmax, a[j]);
			while(sz(pq) && cnt[pq.top()] <= 0) pq.pop();
			int w = curmax;
			if(sz(pq)) w = max(w, pq.top());
			if(w == 0) ret = max(ret, z - j + 2 * dp[j - 1][z]);
			else{
				ret = max(ret, plen + 2 * (sum[c] - sum[w - 1]) - 2 * max(cnt[w], 0));
			}
		}
	};
	for(int i = 1; i <= n; i++){
		int j = i + 1 - dp[i][i], k = i + dp[i][i];
		Do(j, k);
	}	
	for(int i = 1; i <= n - 1; i++){
		int j = i + 1 - dp[i][i + 1], k = i + 1 + dp[i][i + 1];
		Do(j, k);
	}
	return ret;
}

int solve(vector<int> a){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			dp[i][j] = (a[i] == a[j] ? (dp[i - 1][j + 1] + 1) : 0);
		}
	}
	return max(solve_case1(a), solve_case2(a));
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	cin >> n >> c;
	vector<int> a(n + 1);
	vector<int> cnt(c + 1);
	for(int i = 1; i <= n; i++) cin >> a[i], cnt[a[i]]++;
	int ret = solve(a);
	reverse(a.begin() + 1, a.end());
	for(auto &y : a) y = c + 1 - y;
	ret = max(ret, solve(a));
	ret = max(ret, *max_element(all(cnt)));
	cout << ret << "\n";
}
