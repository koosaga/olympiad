#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
using lint = long long;
using pi = pair<int, int>;
 
int n, m, c[MAXN];
pi a[MAXN];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++) scanf("%d %d",&a[i].second,&a[i].first);
	sort(a + 1, a + n + 1);
	for(int i=1; i<=m; i++) scanf("%d",&c[i]);
	sort(c + 1, c + m + 1);
	int dap = 0;
	int ptr = n;
	for(int i=m; i; i--){
		while(ptr > 0 && a[ptr].second > c[i]) ptr--;
		if(ptr > 0){
			ptr--;
			dap++;
		}
	}
	cout << dap << endl;
}
