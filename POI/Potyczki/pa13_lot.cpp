#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005050;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

char str[MAXN];

int main(){
	int n; cin >> n;
	scanf("%s", str);
	int dp[3] = {};
	for(int i=0; str[i]; i++){
		int w = str[i] - 'A';
		int nxt[3]; memset(nxt, 0x3f, sizeof(nxt));
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				if(j != k) nxt[j] = min(nxt[j], dp[k]);
			}
			if(j != w) nxt[j]++;
		}
		memcpy(dp, nxt, sizeof(dp));
	}
	cout << *min_element(dp, dp + 3) << endl;
}
