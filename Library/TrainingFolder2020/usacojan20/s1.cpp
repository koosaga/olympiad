#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int n, k, a[MAXN];
int cnt[MAXN];

int main(){
	freopen("berries.in", "r", stdin);
	freopen("berries.out", "w", stdout);
	cin >> n >> k;
	for(int i=0; i<n; i++) cin >> a[i];
	int dap = 0;
	for(int i=1; i<=1000; i++){
		memset(cnt, 0, sizeof(cnt));
		for(int j=0; j<n; j++){
			cnt[i] += a[j] / i;
			if(a[j] % i){
				cnt[a[j] % i] += 1;
			}
		}
		vector<int> seq;
		for(int j=i; j>=1; j--){
			while(sz(seq) < k && cnt[j]){
				seq.push_back(j);
				cnt[j]--;
			}
		}
		while(sz(seq) < k) seq.push_back(0);
		int ret = accumulate(seq.begin() + k / 2, seq.begin() + k, 0);
		dap = max(dap, ret);
	}
	cout << dap << endl;
}
