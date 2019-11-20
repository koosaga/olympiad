#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 800005;

int atoi(char c){
	return c - '0';
}

int main(){
	auto calc = [&](string t){
		int h = atoi(t[0])*10 + atoi(t[1]);
		int m = atoi(t[3])*10 + atoi(t[4]);
		int s = atoi(t[6])*10 + atoi(t[7]);
		return 3600*h+60*m+s;
	};
	int n, m; cin >> n >> m;
	vector<tuple<int, int, string>> ans;
	for(int i=0; i<n+1; i++){
		string s; cin >> s;
		int solved = 0, penalty = 0;
		for(int j=0; j<m; j++){
			string t; cin >> t;
			if(t[0] == '?') t[0] = '+';
			if(t[0] == '+'){
				solved++;
				penalty += 1200 * (t[1] - '1');
				t = t.substr(3, sz(t) - 3);
				penalty += calc(t);
			}
		}
		if(i < n && s == "NijeZivotJedanACM") continue;
		ans.emplace_back(-solved, penalty, s);
	}
	int foo = 0;
	for(int i=0; i<sz(ans); i++){
		if(ans[i] <= ans.back()) foo++;
	}
	cout << foo << endl;
}
