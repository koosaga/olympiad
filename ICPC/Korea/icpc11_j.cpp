#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int n, m;
pi a[MAXN], b[MAXN];

int main(){
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0; i<n; i++) scanf("%d %d",&a[i].second,&a[i].first);
		scanf("%d",&m);
		for(int i=0; i<m; i++) scanf("%d %d",&b[i].second,&b[i].first);
		sort(a, a + n);
		sort(b, b + m);
		int ans = 1e9;
		for(int i=0; i<2; i++){
			int ptr = 0, foo = 1e9;
			for(int i=0; i<n; i++){
				while(ptr < m && b[ptr].first <= a[i].first){
					foo = min(foo, -b[ptr].first + b[ptr].second);
					ptr++;
				}
				ans = min(ans, foo + a[i].first - a[i].second);
			}
			reverse(a,a+n); reverse(b,b+m);
			for(int i=0; i<n; i++) a[i].first *= -1;
			for(int i=0; i<m; i++) b[i].first *= -1;
		}
		cout << ans << endl;
	}
}
