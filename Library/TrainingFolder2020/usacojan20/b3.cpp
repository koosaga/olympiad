#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int k, n;

lint sum(int x){
	return 1ll * x * (x + 1) / 2;
}

int main(){
	freopen("race.in", "r", stdin);
	freopen("race.out", "w", stdout);
	cin >> k >> n;
	int nobaggu = 0;
	while(sum(nobaggu) < k) nobaggu++;
	for(int i=0; i<n; i++){
		int q; cin >> q;
		if(nobaggu < q){
			q = nobaggu;
		}
		int ans = 1e9;
		for(int qq = max(q - 2, 0); qq <= q; qq++){
			for(int j=0; j<33333; j++){
				if(sum(j + qq) + sum(j + qq - 1) - sum(qq - 1) >= k){
					ans = min(ans, j * 2 + qq);
				}
				if(sum(j + qq) + sum(j + qq ) - sum(qq - 1) >= k){
					ans = min(ans, j * 2 + qq + 1);
				}
			}
		}
			cout << ans << endl;
	}
}
