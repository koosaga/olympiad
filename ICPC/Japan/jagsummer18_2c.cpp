#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1000005;

vector<lint> enum_all_yaksu(lint n){
	vector<lint> ans;
	for(lint i=1; i*i<=n; i++){
		if(n%i == 0){
			ans.push_back(i);
			ans.push_back(n/i);
		}
	}
	sort(all(ans));
	ans.resize(unique(all(ans)) - ans.begin());
	return ans;
}

int main(){
	lint n; cin >> n;
	lint ret = 0;
	auto y1 = enum_all_yaksu(2 * n);
	auto y2 = enum_all_yaksu(n);
	for(auto &i : y1){
		if(i % 2 == 0 && i >= 3 && i <= n){
			ret += n / i;
			if(binary_search(all(y2), i)) ret--;
		}
	}
	for(auto &i : y2){
		if(i >= 3 && i <= n){
			ret += 1;
		}
	}
	cout << ret << endl;
}
