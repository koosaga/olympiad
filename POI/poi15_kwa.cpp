#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 10005;

const int foo[31] = {
128,
112,
108,
96,
92,
76,
72,
67,
60,
48,
47,
44,
43,
33,
32,
31,
28,
27,
24,
23,
22,
19,
18,
15,
12,
11,
8,
7,
6,
3,
2};

int dp[MAXN];

lint g(lint x){
	return (x * (x + 1) / 2) * (2 * x + 1) / 3;
}

int main(){
	fill(dp + 1, dp + MAXN, 1e9);
	for(int i=1; i<=100; i++){
		for(int j=10000; j>=i*i; j--){
			dp[j] = min(dp[j], max(dp[j-i*i], i));
		}
	}
	lint n; cin >> n;
	if(n <= 10000){
		int ret = 0;
		for(int i=1; i<=n; i++){
			if(dp[i] > 1e8){
				ret++;
				dp[i] = -1;
			}
			else{
				if(g(dp[i] - 1) >= i){
					if(dp[i] >= 20){
						assert(find(foo, foo + 31, g(dp[i] - 1) - i) != foo + 31);
					}
					ret++;
				}
			}
		}
		if(dp[n] == -1) printf("-");
		else printf("%d", dp[n]);
		printf(" %d\n", ret);
		return 0;
	}
	lint ret = 0;
	for(int i=1; i<=10000; i++){
		if(dp[i] > 1e8) ret++;
		if(dp[i] < 20 && g(dp[i] - 1) >= i) ret++;
	}
	int pos = 0;
	int s = 0, e = 2e6;
	while(s != e){
		int m = (s+e)/2;
		if(g(m) >= n) e = m;
		else s = m + 1;
	}
	pos = s;
	for(int i=20; i<2000000; i++){
        lint gg = g(i-1);
        if(gg > n + 1000) break;
        if(gg < n - 1000){
        	ret += 31;
        	continue;
		}
		for(int j=0; j<31; j++){
			lint foov = gg - foo[j];
			if(foov <= n) ret++;
			if(foov == n){
				pos = i;
			}
		}
	}
	cout << pos << " " << ret << endl;
}

