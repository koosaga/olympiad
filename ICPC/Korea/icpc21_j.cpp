#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1000005;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	vector<pi> a(3);
	for(int i = 0; i < 3; i++){
		cin >> a[i].first;
		a[i].second = i + 1;
	}
	vector<pi> ans;
	while(1){
		sort(all(a));
		if(a[0].first == 0) break;
		lint d = a[1].first % a[0].first;
		lint q = a[1].first / a[0].first;
		auto send = [&](int s, int t){
			assert(a[s].first >= a[t].first);
			a[s].first -= a[t].first;
			a[t].first *= 2;
			ans.emplace_back(a[s].second, a[t].second);
		};
		if(d <= a[0].first / 2){
			int k = 40;
			while((q >> k) == 0) k--; 
			for(int i = 0; i <= k; i++){
				if((q >> i) & 1) send(1, 0);
				else send(2, 0);
			}
		}
		else{
			q++;
			int k = 40;
			while((q >> k) == 0) k--; 
			for(int i = 0; i < k; i++){
				if((q >> i) & 1) send(1, 0);
				else send(2, 0);
			}
			send(0, 1);
		}
	}
	cout << sz(ans) << "\n";
	for(auto &[x, y] : ans) cout << x << ' ' << y << '\n';
}
