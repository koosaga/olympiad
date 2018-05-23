#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int MAXN = 200005;

int n, k, a[MAXN];
int cnt[MAXN], thres[MAXN], req;

int main(){
	int q;
	scanf("%d %d %d",&n,&k,&q);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=0; i<q; i++){
		int x, v;
		scanf("%d %d",&x,&v);
		thres[x] = v;
	}
	int req = q;
	int e = 1, ans = 1e9;
	for(int i=1; i<=n; i++){
		cnt[a[i]]++;
		if(cnt[a[i]] == thres[a[i]]) req--;
		while(e <= i && cnt[a[e]] > thres[a[e]]){
			cnt[a[e]]--;
			e++;
		}
		if(req == 0){
			ans = min(ans, i - e + 1);
		}
	}
	if(ans > 1e6) puts("impossible");
	else cout << ans << endl;
}
