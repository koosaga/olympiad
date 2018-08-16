#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 300005;

int n;
vector<int> divi;
vector<set<int>> ans;

int main(){
	cin >> n;
	for(int i=1; i*i<=n; i++){
		if(n % i == 0){
			divi.push_back(i);
			if(i * i != n) divi.push_back(n / i);
		}
	}
	sort(divi.begin(), divi.end());
	ans.resize(divi.size());
	ans[0].insert(0);
	for(int i=1; i<divi.size(); i++){
		for(int j=0; j<i; j++){
			if(divi[i] % divi[j] == 0){
				for(auto &k : ans[j]){
					ans[i].insert(k + (divi[i] / divi[j]) - 1);
				}
			}
		}
	}
	cout << ans.back().size() << endl;
	for(auto &i : ans.back()) printf("%d ", i);
}
