#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int n;
pi a[MAXN];

int main(){
	int tc; cin >> tc;
	while(tc--){
		map<string, int> cnt;
		cin >> n;
		vector<string> T(n), S(n);
		for(int i=0; i<n; i++){
			cin >> T[i] >> S[i]; scanf("%*d %*d");
			cnt[S[i]]++;
		}
		vector<string> stk;
		map<string, int> cur;
		vector<int> chk(n, 1);
		for(int i=0; i<n; i++){
			if(sz(stk) == 60) break;
			if(cur[S[i]] == (cnt[S[i]] + 1) / 2) continue;
			if(i < 10){
				if(cur[S[i]] > 3) continue;
				cur[S[i]]++;
				chk[i] = 0;
				stk.push_back(T[i]);
			}
			else if(i < 20){
				if(cur[S[i]] > 2) continue;
				cur[S[i]]++;
				chk[i] = 0;
				stk.push_back(T[i]);
			}
			else if(i < 30){
				if(cur[S[i]] > 1) continue;
				cur[S[i]]++;
				chk[i] = 0;
				stk.push_back(T[i]);
			}
			else{
				if(cur[S[i]] > 0) continue;
				cur[S[i]]++;
				chk[i] = 0;
				stk.push_back(T[i]);
			}
		}
		for(int i=0; i<n; i++){
			if(sz(stk) < 60 && chk[i]){
				chk[i] = 0;
				stk.push_back(T[i]);
			}
		}
		for(int i=n-1; i>=0; i--){
			if(!chk[i]){
				cout << T[i] << endl;
				break;
			}
		}
	}
}
