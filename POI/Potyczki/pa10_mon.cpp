#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;

int n, k;

char str[MAXN];

int main(){
	scanf("%d %d",&n,&k);
	scanf("%s", str);
	lint cur = 0;
	int ret = 0;
	map<lint, int> mp;
	for(int i = 0; str[i]; i++){
		if(mp.find(cur) == mp.end()) mp[cur] = i;
		if(str[i] == 'O') cur++;
		else cur -= k;
		if(mp.find(cur) != mp.end()) ret = max(ret, i + 1 - mp[cur]);
	}
	cout << ret << endl;
}
