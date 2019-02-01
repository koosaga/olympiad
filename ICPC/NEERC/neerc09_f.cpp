#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXM = 1005;
#define sz(v) int((v).size())

priority_queue<pair<int, string>, vector<pair<int, string>> ,greater<pair<int, string> >> pq;
queue<string> que;
set<string> avoid;

int n, m, len[MAXM], A[MAXM][26];

int f(string s){
	int cnt[26] ={};
	for(int i=0; i<s.size(); i++) cnt[s[i] - 'A']++;
	int ret = 0;
	vector<int> v;
	for(int i=0; i<26; i++) if(cnt[i]) v.push_back(i);
	for(int j=0; j<m; j++){
		if(len[j] < sz(s)) continue;
		int bad = 1;
		for(auto &k : v){
			if(cnt[k] > A[j][k]){
				bad = 0;
				break;
			}
		}
		ret += bad;
	}
	return ret;
}

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		string s;
		cin >> s;
		for(int j=0; j<26; j++){
			A[i][j] = count(s.begin(), s.end(), j + 'A');
		}
		len[i] = s.size();
		avoid.insert(s);
	}
	for(int i='A'; i<='Z'; i++){
		string s;
		s.push_back(i);
		que.push(s);
	}
	while(!que.empty()){
		auto x = que.front(); que.pop();
		int cnt = f(x);
		if(pq.size() == n && pq.top().first >= cnt) continue;
		if(avoid.find(x) == avoid.end()){
			pq.emplace(cnt, x);
			if(pq.size() > n) pq.pop();
		}
		for(int i='A'; i<='Z'; i++){
			x.push_back(i);
			que.push(x);
			x.pop_back();
		}
	}
	while(!pq.empty()){
		cout << pq.top().second << endl;
		pq.pop();
	}
}
