#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int main(){
	string s;
	int n;
	cin >> s >> n;
	vector<string> ret;
	for(int i=0; i<n; i++){
		string t;
		cin >> t;
		bool ok = 1;
		for(int i=0; i<t.size(); i++){
			if(s[i] == '*'){
				continue;
			}
			if(s[i] != t[i]) ok = 0;
		}
		if(ok) ret.push_back(t);
	}
	cout << ret.size() << endl;
	for(auto &i : ret) cout << i << endl;
}

