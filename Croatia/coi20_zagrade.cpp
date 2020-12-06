// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

int query(int s, int e){
	printf("? %d %d\n", s+1, e+1);
	fflush(stdout);
	int x; scanf("%d",&x);
	return x;
}

char str[MAXN];

int main(){
	int n, q; cin >> n >> q;
	vector<int> stk = {0};
	for(int i=1; i<n; i++){
		if(query(stk.back(), i)){
			str[stk.back()] = '(';
			str[i] = ')';
			stk.pop_back();
		}
		else stk.push_back(i);
	}
	for(int i=0; i<sz(stk)/2; i++) str[stk[i]] = ')';
	for(int i=sz(stk)/2; i<sz(stk); i++) str[stk[i]] = '(';
	cout << "! " << str << endl;
}
