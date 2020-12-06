#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;

int n, a[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	int cnt = 0;
	for(int i=1; i<=n; ){
		int j = i;
		if(cnt % 2 == 0){
			while(j+1 <= n && a[j] <= a[j+1]) j++;
			cnt++;
		}
		else{
			while(j+1 <= n && a[j] >= a[j+1]) j++;
			cnt++;
		}
		i = j + 1;
	}
	int ans = 0;
	for(int i = cnt; i > 1; i = (i + 1) / 2) ans++;
	cout << ans << endl;
}