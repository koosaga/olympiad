#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 105050;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main(){
	int n; cin >> n;
	for(int i=30000; i; i--){
		if(n % (i * i) == 0){
			int w = n / (i * i);
			printf("%lld\n", 1ll * n * w);
			return 0;
		}
	}
}
