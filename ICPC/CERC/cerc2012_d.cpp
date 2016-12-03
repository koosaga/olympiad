#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int low[200005], high[200005];
int n, a[200005];

int solve(int s, int e){
	if(s > e) return 1;
	int p1 = s, p2 = e;
	while(p1 <= p2){
		if(low[p1] < s && high[p1] > e){
			return solve(s, p1-1) && solve(p1+1, e);
		}
		if(low[p2] < s && high[p2] > e){
			return solve(s, p2-1) && solve(p2+1, e);
		}
		p1++;
		p2--;
	}
	return 0;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
		}
		map<int, int> mp;
		for(int i=1; i<=n; i++){
			if(mp.find(a[i]) != mp.end()){
				low[i] = mp[a[i]];
			}
			else low[i] = 0;
			mp[a[i]] = i;
		}
		mp.clear();
		for(int i=n; i; i--){
			if(mp.find(a[i]) != mp.end()){
				high[i] = mp[a[i]];
			}
			else high[i] = n+1;
			mp[a[i]] = i;
		}
		puts(solve(1, n) ? "non-boring" : "boring");
	}
}a