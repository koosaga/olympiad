#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int MAXN = 150005;
const int mod = 1e9 + 7;

lint dp[MAXN];
lint n;
int p, q;

int main(){
	cin >> n >> p >> q;
	dp[0] = 1;
	int limit = MAXN;
	for(int i=0; i<limit; i++){
		if(!dp[i]) continue;
		for(int j=2; i+j*p+q<limit; j++){
			dp[i + j * p + q] = max(dp[i + j * p + q], dp[i] * j);
			if(dp[i] * j >= n){
				limit = i + j * p + q;
				break;
			}
		}
	}
	cout << limit << endl;
}
