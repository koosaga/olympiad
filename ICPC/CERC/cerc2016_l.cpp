#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 300005;

vector<string> ans;
vector<int> rep[8];
int n, a[111];

string tostr(int x){
	char buf[10];
	sprintf(buf, "%d", x);
	string ret = buf;
	return ret;
}

string name(int x){
	if(x < 0){
		x = ~x;
		return "!x" + tostr(x + 1);
	}
	return "x" + tostr(x + 1);
}

string gen(int x, int y){
	return name(x) + " -> " + name(y);
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<3; i++){
		int v;
		for(int j=0; j<n; j++){
			scanf("%d",&v);
			a[j] |= (v<<i);
		}
	}
	for(int i=0; i<n; i++){
		if(a[i] == 0) ans.push_back(gen(i, ~i));
		else if(a[i] == 7) ans.push_back(gen(~i, i));
		else rep[a[i]].push_back(i);
	}
	for(int i=1; i<=6; i++){
		for(int j=1; j<rep[i].size(); j++){
			ans.push_back(gen(rep[i][0], rep[i][j]));
			ans.push_back(gen(~rep[i][0], ~rep[i][j]));
		}
	}
	vector<int> visib;
	for(int i=1; i<=3; i++){
		if(rep[i].size() && rep[7-i].size()){
			ans.push_back(gen(rep[i][0], ~rep[7-i][0]));
			ans.push_back(gen(~rep[i][0], rep[7-i][0]));
		}
		if(rep[i].size() || rep[7-i].size()) visib.push_back(i);
	}
	if(visib.size() == 1 || visib.size() == 3){
		puts("-1");
		return 0;
	}
	if(visib.size() == 2){
		if(visib[0] == 1 && visib[1] == 2){
			int lv = (rep[1].size() ? rep[1][0] : ~rep[6][0]);
			int rv = ~(rep[2].size() ? rep[2][0] : ~rep[5][0]);
			ans.push_back(gen(lv, rv));
		}
		if(visib[0] == 1 && visib[1] == 3){
			int lv = (rep[1].size() ? rep[1][0] : ~rep[6][0]);
			int rv = (rep[3].size() ? rep[3][0] : ~rep[4][0]);
			ans.push_back(gen(lv, rv));
		}
		if(visib[0] == 2 && visib[1] == 3){
			int lv = (rep[2].size() ? rep[2][0] : ~rep[5][0]);
			int rv = (rep[3].size() ? rep[3][0] : ~rep[4][0]);
			ans.push_back(gen(lv, rv));
		}
	}
	cout << ans.size() << endl;
	for(auto &i : ans) cout << i << endl;
}
