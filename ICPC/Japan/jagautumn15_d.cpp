#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

string s;
int n;

int query(int l, int r){
	int pos = l;
	while(true){
		if(s[pos] == '<') pos = --l;
		else if(s[pos] == '>') pos = ++r;
		if(l < 0 || r >= n) return r - l;
	}
}
int main(){
	cin >> n >> s;
	int st = 0, ed = n - 1;
	while(st != ed){
		int m = (st+ed)/2;
		if(query(m, m) < query(m+1, m+1)) st = m+1;
		else ed = m;
	}
	cout << query(st, st);
}
