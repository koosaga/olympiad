#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

int main(){
	freopen("isharp.in", "r", stdin);
	freopen("isharp.out", "w", stdout);
	string s; cin >> s;
	string x;
	while(cin >> x){
		string t = s;
		string alp, acc;
		for(int i=0; i+1<x.size(); i++){
			if(isalpha(x[i])){
				alp.push_back(x[i]);
			}
			else{
				acc.push_back(x[i]);
			}
		}
		reverse(acc.begin(), acc.end());
		for(int i=1; i<acc.size(); i++){
			if(acc[i-1] == ']' && acc[i] == '[') swap(acc[i-1], acc[i]);
		}
		t += acc;
		t += " ";
		t += alp;
		cout << t << ";" << endl;
	}
}

