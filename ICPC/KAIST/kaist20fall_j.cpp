#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 1005;
using lint = long long;
using pi = pair<int, int>;

int n;
pi a[MAXN];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i].first >> a[i].second;
	vector<int> v(n); iota(all(v), 0);
	sort(all(v), [&](const int &p, const int &q){ return a[p] < a[q]; });
	printf("%d\n", 2*n-1);
	for(int i=0; i<n; i++) printf("%d ", v[i] + 1);
	for(int i=n-2; i>=0; i--) printf("%d ", v[i] + 1);
}
