#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 998244353;
const int MAXN = 1000005;

int n, t, a[MAXN];

int main(){
	scanf("%d %d",&n,&t);
	for(int i=0; i<n; i++) scanf("%d",&a[i]), a[i]--;
	int sum = accumulate(a, a + n, 0);
	lint ret = t - n - sum + 1;
	for(int i=1; i<n; i++){
		sum -= a[i - 1];
		ret = ret * (t + 1 - sum) % mod;
	}
	cout << ret << endl;
}
