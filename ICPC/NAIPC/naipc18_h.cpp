#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int mod = 1e9 + 7;
typedef long long lint;

char ans[55][55];
int cs[55], ct[55];
string s, t;
int n, m;

bool insane(){
	int ans = 0;
	for(int i=0; i<s.size(); i++) ans ^= s[i] - '0';
	for(int i=0; i<t.size(); i++) ans ^= t[i] - '0';
	return ans;
}

int main(){
	cin >> s >> t;
	n = s.size();
	m = t.size();
	if(insane()){
		puts("-1");
		return 0;
	}
	string ret;
	for(int i=0; i<s.size(); i++){
		for(int j=0; j<t.size(); j++){
			cs[i] ^= 1;
			ct[j] ^= 1;
			ans[i][j] = '1';
		}
	}
	vector<int> f1, f2;
	for(int i=0; i<s.size(); i++) cs[i] ^= (s[i] - '0');
	for(int i=0; i<t.size(); i++) ct[i] ^= (t[i] - '0');
	for(int i=0; i<s.size(); i++) if(cs[i]) f1.push_back(i);
	for(int i=0; i<t.size(); i++) if(ct[i]) f2.push_back(i);
	if(f1.size() > f2.size()){
		for(int i=0; i<f1.size()-f2.size(); i++){
			ans[f1[i]][0] = '0';
		}
		for(int i=0; i<f2.size(); i++){
			ans[f1[i + f1.size() - f2.size()]][f2[i]] = '0';
		}
	}
	else{
		for(int i=0; i<f2.size()-f1.size(); i++) ans[0][f2[i]] = '0';
		for(int i=0; i<f1.size(); i++){
			ans[f1[i]][f2[i + f2.size()-f1.size()]] = '0';
		}
	}
	for(int i=0; i<n; i++) puts(ans[i]);
}
