#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 4005;
const lint mx = 2e18;

vector<int> duval(string s){
	int n = sz(s);
	vector<int> v;
	for(int i = 0; i < n; ){
		int j = i + 1, k = i;
		while(j < n && s[k] <= s[j]){
			if(s[k] == s[j]) j++, k++;
			else if(s[k] < s[j]) j++, k = i;
		}
		while(i <= k){
			i += j - k;
			v.push_back(i);
		}
	}
	return v;
}

int main(){
	int n; cin >> n;
	string s; cin >> s;
	int ptr = 0;
	while(ptr < n && s[ptr] == '1') ptr++;
	if(ptr == n){
		cout << "0 0\n";
		return 0;
	}
	s = s.substr(ptr);
	for(auto &i : s) i ^= 1;
	s += "2";
	auto ans = duval(s);
	int i = ans[sz(ans) - 2] + ptr;
	cout << ptr << " " << (i - ptr) << "\n";
}
