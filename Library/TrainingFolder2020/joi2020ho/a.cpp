#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;

int n;
pi a[MAXN];
int b[MAXN];
int pref[MAXN], suff[MAXN];
int ans[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n+1; i++){
		scanf("%d",&a[i].first);
		a[i].second = i;
	}
	for(int i=1; i<=n; i++) scanf("%d",&b[i]);
	sort(a + 1, a + n + 2);
	sort(b + 1, b + n + 1);
	for(int i=1; i<=n; i++){
		pref[i] = max(pref[i - 1], a[i].first - b[i]);
	}
	for(int i=n; i; i--){
		suff[i] = max(suff[i + 1], a[i + 1].first - b[i]);
	}
	for(int i=1; i<=n+1; i++){
		ans[a[i].second] = max(pref[i-1], suff[i]);
	}
	for(int i=1; i<=n+1; i++) printf("%d ", ans[i]);
}
