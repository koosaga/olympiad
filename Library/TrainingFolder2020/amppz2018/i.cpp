#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 500005;

int n;
pi a[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		a[i] = pi(-x + y, x + y);
	}
	sort(a, a + n);
	vector<int> ans;
	for(int i=0; i<n; i++){
		auto l = lower_bound(ans.begin(), ans.end(), -a[i].second);
		if(l == ans.end()) ans.push_back(-a[i].second);
		else *l = -a[i].second;
	}
	cout << ans.size() << endl;
}
