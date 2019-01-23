#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5005;
using pi = pair<int, int>;

int n;
string s[MAXN];

vector<pi> token(string s){
	vector<pi> v;
	for(int i=0; i<s.size(); ){
		if(isalpha(s[i])){
			v.emplace_back(1, s[i]);
			i++;
		}
		else{
			int e = i;
			while(e < s.size() && isdigit(s[e])) e++;
			int ans = 0;
			for(int j=i; j<e; j++) ans = ans * 10 + s[j] - '0';
			v.emplace_back(0, ans);
			i = e;
		}
	}
	return v;
}

bool cmp(string a, string b){
	auto va = token(a);
	auto vb = token(b);
	return va <= vb;
}

int main(){
	cin >> n;
	for(int i=0; i<=n; i++) cin >> s[i];
	for(int i=1; i<=n; i++){
		if(cmp(s[0], s[i])) puts("+");
		else puts("-");
	}
}
