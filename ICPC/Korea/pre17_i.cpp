#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n, m, a[1005], b[1005];
lint sum;

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int x;
			scanf("%d",&x);
			a[i] = max(a[i], x);
			b[j] = max(b[j], x);
			sum += x;
		}
	}
	set<int> s;
	for(int i=0; i<n; i++) s.insert(a[i]);
	for(int i=0; i<m; i++) s.insert(b[i]);
	for(auto &i : s) sum -= i;
	cout << sum;
}


