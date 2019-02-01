#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 100005;
using pi = pair<int, int>;
#define sz(v) int((v).size())

int a[MAXN], n;

double solve(deque<int> dq){
	double ret = a[dq.front()] + a[dq.back()];
	for(int i=1; i<dq.size(); i++) ret += sqrt(4.0 * a[dq[i-1]] * a[dq[i]]);
	return ret;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) cin >> a[i];
	sort(a, a + n);
	reverse(a, a + n);
	deque<int> dq;
	int l = 0, r = n, sgn = 0;
	while(r - l >= 2){
		if(!sgn){
			dq.push_front(l++);
			dq.push_back(--r);
		}
		else{
			dq.push_front(--r);
			dq.push_back(l++);
		}
		sgn ^= 1;
	}
	double ret = 1e18;
	if(n % 2 == 0) ret = solve(dq);
	else{
		dq.push_back(n / 2);
		ret = solve(dq);
		dq.pop_back();
		dq.push_front(n / 2);
		ret = min(ret, solve(dq));
	}
	printf("%.10f\n", ret);
}
