#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

char buf[10005];
string t1, t2, t3;

void solve(){
	set<string> ban;
	vector<string> v;
	fgets(buf, 10005, stdin);
	string s;
	for(int i=0; buf[i]; i++){
		if(buf[i] == ' ' || buf[i] == '\n'){
			v.push_back(s);
			s.clear();
		}
		else s.push_back(buf[i]);
	}
	while(1){
		cin >> t1 >> t2 >> t3;
		if(t2 == "goes"){
			ban.insert(t3);
		}
		else{
			scanf("%*s %*s\n");
			break;
		}
	}
	for(auto &i : v){
		if(ban.find(i) == ban.end()) cout << i << " ";
	}
	puts("");
}

int main(){
	int t;
	scanf("%d\n",&t);
	while(t--) solve();
}