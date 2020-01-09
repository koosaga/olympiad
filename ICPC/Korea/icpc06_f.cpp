#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 30005;

int n, a[32], b[32], m;

void solve(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i] >> b[i];
	cin >> m;
	for(int i=0; i<200000; i+=n){
		int k = i / n;
		int tmp = 0;
		bool good = 1;
		for(int j=0; j<n; j++){
			if(k % a[j] == b[j] % a[j] && k >= b[j]){
				tmp += (k - b[j]) / a[j];
			}
			else{
				good = 0;
				break;
			}
		}
		if(good && tmp == m){
			cout << k << endl;
			return;
		}
	}
	puts("0");
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
}
