#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using pi = pair<int, int>;

int n, a[MAXN], fail[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=n-1; i>=0; i--) scanf("%d",&a[i]);
	int p = 0;
	for(int i=1; i<n; i++){
		while(p && a[i] != a[p]) p = fail[p];
		if(a[i] == a[p]) p++;
		fail[i + 1] = p;
	}
	pi ret(1e9, 1e9);
	for(int i=1; i<=n; i++){
		int k = n - i;
		int p = i - fail[i];
		ret = min(ret, pi(k + p, p));
	}
	cout << ret.first - ret.second << " " << ret.second << endl;
}
