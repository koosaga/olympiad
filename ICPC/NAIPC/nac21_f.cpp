#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 1000005;

int n, a[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	int ans = 0;
	for(int i=0; i<n; i++){
		int p = 0;
		while(i + p + 1 < n && i - p - 1 >= 0 && a[i-p-1] == a[i+p+1]){
			if(a[i+p] <= a[i+p+1]) break;
			p++;
		}
		ans = max(ans, 2 * p + 1);
	}
	for(int i=1; i<n; i++){
		if(a[i-1] != a[i]) continue;
		int p = 0;
		while(i + p + 1 < n && i - p - 2 >= 0 && a[i-p-2] == a[i+p+1]){
			if(a[i+p] <= a[i+p+1]) break;
			p++;
		}
		ans = max(ans, 2 * p + 2);
	}
    if(ans < 3) ans = -1;
	cout << ans << endl;
}
