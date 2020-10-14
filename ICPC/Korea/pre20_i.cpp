#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int MAXN = 250005;
const int MAXT = 530000;

int n, a[MAXN];

int main(){
	scanf("%d",&n);
	n*=2;
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a, a+n);
	int ret = 1e9;
	for(int i=0; i<n/2; i++) ret = min(ret, a[i]+a[n-1-i]);
	cout << ret << endl;
}
