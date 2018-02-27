#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

vector<int> v;

int main(){
	int n, k, p;
	scanf("%d %d %d",&n,&k,&p);
	for(int i=1; i<n; i++){
		int q;
		scanf("%d",&q);
		v.push_back(q - p - 1);
		p = q;
	}
	sort(v.begin(), v.end());
	int ans = n;
	for(int i=0; i<n-k; i++) ans += v[i];
	cout << ans << endl;
}
