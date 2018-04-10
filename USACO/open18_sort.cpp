#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;

int n, a[MAXN];
int ans[MAXN];

vector<pi> v;

int main(){
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		v.push_back(pi(a[i], i));
	}
	sort(v.begin(), v.end());
	for(int i=1; i<=n; i++){
		a[i] = lower_bound(v.begin(), v.end(), pi(a[i], i)) - v.begin() + 1;
	}
	if(is_sorted(a, a+n+1)){
		cout << n - (n == 1) << endl;
		return 0;
	}
	for(int i=1; i<=n; i++){
		if(a[i] < i){
			ans[a[i]] = max(ans[a[i]], i - a[i]);
			ans[a[i]+1] = max(ans[a[i] + 1], i - a[i]);
		}
	}
	for(int i=1; i<=n; i++) ans[i] = max(ans[i], ans[i-1] - 1);
	cout << accumulate(ans + 1, ans + n + 1, 0ll);
}
