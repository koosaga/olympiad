#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
 
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int Q; cin >> Q;
	while(Q--){
		string s, t;
		cin >> s >> t;
		vector<int> cnt(256);
		for(int i = 0; i < sz(s); i++){
			cnt[s[i]]++;
		}
		for(int i = 0; i < sz(t); i++){
			cnt[t[i]]--;
		}
		if(*min_element(all(cnt)) < 0){
			cout << "NO\n";
			continue;
		}
		string q;
		for(int i = 0; i < sz(s); i++){
			if(cnt[s[i]] == 0) q.push_back(s[i]);
			else cnt[s[i]]--;
		}
		if(t == q) cout << "YES\n";
		else cout << "NO\n";
	}
}
