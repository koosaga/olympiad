#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k, s; cin >> n >> k >> s;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(all(a));
	reverse(all(a));
	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += a[i];
		if(sum >= k * s){
			cout << i+1;
			return 0;
		}
	}
}
