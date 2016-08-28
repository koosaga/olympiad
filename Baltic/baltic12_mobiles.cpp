#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;

int n, l;
pi a[1000005];
deque<pi> stk;

double cross(pi a, pi b){
	int x1 = a.first, x2 = b.first, y1 = a.second, y2 = b.second;
	return 1.0 * (1ll * x2 * x2 + 1ll * y2 * y2 - 1ll * x1 * x1 - 1ll * y1 * y1) / (2.0 * (x2 - x1));
}

double solve(double s, double e, pi t){
	return max(hypot(s - t.first, t.second), hypot(e - t.first, t.second));
}

int main(){
	scanf("%d %d",&n,&l);
	for (int i=0; i<n; i++) {
		scanf("%d %d",&a[i].first, &a[i].second);
		a[i].second = abs(a[i].second);
	}
	sort(a, a+n);
	for (int i=0; i<n; ) {
		int e = i;
		while(e < n && a[e].first == a[i].first) e++;
		while (stk.size() >= 2 && cross(stk[stk.size()-2], stk.back()) > cross(stk.back(), a[i])) {
			stk.pop_back();
		}
		stk.push_back(a[i]);
		i = e;
	}
	double ret = 0;
	while(stk.size() >= 2 && cross(stk[0], stk[1]) < 0) stk.pop_front();
	while(stk.size() >= 2 && cross(stk[stk.size()-2], stk.back()) > l) stk.pop_back();
	ret = max(ret, solve(0, cross(stk[0], stk[1]), stk[0]));
	ret = max(ret, solve(cross(stk[stk.size()-2], stk.back()), l, stk.back()));
	for(int i=1; i+1<stk.size(); i++){
		ret = max(ret, solve(cross(stk[i-1], stk[i]), cross(stk[i], stk[i+1]), stk[i]));
	}
	printf("%lf",ret);
}