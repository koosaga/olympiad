#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 100005;
using pi = pair<int, int>;
#define sz(v) int((v).size())

bool ends(string s, string t){
	if(s.size() >= t.size() && s.substr(s.size() - t.size(), t.size()) == t) return 1;
	return 0;
}

string trim(string s, string t){
	for(auto &i : t) s.pop_back();
	return s;
}

string solve(string s){
	if(ends(s, "a")) return trim(s, "a") + "as";
	if(ends(s, "i")) return trim(s, "i") + "ios";
	if(ends(s, "y")) return trim(s, "y") + "ios";
	if(ends(s, "l")) return trim(s, "l") + "les";
	if(ends(s, "n")) return trim(s, "n") + "anes";
	if(ends(s, "ne")) return trim(s, "ne") + "anes";
	if(ends(s, "o")) return trim(s, "o") + "os";
	if(ends(s, "r")) return trim(s, "r") + "res";
	if(ends(s, "t")) return trim(s, "t") + "tas";
	if(ends(s, "u")) return trim(s, "u") + "us";
	if(ends(s, "v")) return trim(s, "v") + "ves";
	if(ends(s, "w")) return trim(s, "w") + "was";
	return s + "us";
}


int main(){
	int tc;
	cin >> tc;
	while(tc--){
		string s;
		cin >> s;
		cout << solve(s) << endl;
	}
}

