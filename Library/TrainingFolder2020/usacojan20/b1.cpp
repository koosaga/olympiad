#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int main(){
	freopen("word.in", "r", stdin);
	freopen("word.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	string dap;
	int sum = 0;
	for(int i=0; i<n; i++){
		string s; cin >> s;
		if(sum + sz(s) > k){
			dap += "\n";
			sum = sz(s);
		}
		else{
			dap += " ";
			sum += sz(s);
		}
		dap += s;
	}
	dap.erase(dap.begin());
	cout << dap;
}
