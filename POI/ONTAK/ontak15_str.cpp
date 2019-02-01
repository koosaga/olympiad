#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, t1, t2, c1, c2, tc, a[100005];

lint trial(int x){
	int pt = 1;
	lint ret = 1ll * x * tc;
	deque<pi> dq1, dq2, dq3;
	for(int i=1; i<=n; i++){
		while(!dq3.empty() && dq3[0].first <= i - t2){
			dq2.push_back(dq3[0]);
			dq3.pop_front();
		}
		while(!dq2.empty() && dq2[0].first <= i - t1){
			dq1.push_back(dq2[0]);
			dq2.pop_front();
		}
		int needy = a[i];
		int dx = min(x, needy);
		needy -= dx;
		x -= dx;
		while(needy && !dq1.empty()){
			int dx = min(needy, dq1[0].second);
			needy -= dx;
			dq1[0].second -= dx;
			ret += 1ll * dx * c1;
			if(dq1[0].second == 0) dq1.pop_front();
		}
		while(needy && !dq2.empty()){
			int dx = min(needy, dq2.back().second);
			needy -= dx;
			dq2.back().second -= dx;
			ret += 1ll * dx * c2;
			if(dq2.back().second == 0) dq2.pop_back();
		}
		if(needy > 0) return 1e18;
		dq3.push_back(pi(i, a[i]));
	}
	return ret;
}

int main(){
	cin >> n >> t1 >> t2 >> c1 >> c2 >> tc;
	int sum = 0;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		sum += a[i];
	}
	if(t1 < t2){
		swap(t1, t2);
		swap(c1, c2);
	}
	if(c1 > c2) c1 = c2;
	int s = 0, e = sum;
	while(s != e){
		int m = (s+e)/2;
		lint cmp1 = trial(m), cmp2 = trial(m+1);
		if(cmp1 >= 1e17 || cmp1 > cmp2){
			s = m+1;
		}
		else e = m;
	}
	cout << trial(s);
}
