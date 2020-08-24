#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <memory.h> 
#include <math.h> 
#include <assert.h> 
#include <stack> 
#include <queue> 
#include <map> 
#include <set> 
#include <string> 
#include <algorithm> 
#include <iostream> 
#include <functional>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
typedef pair<int, int> pi;
const int MAXN = 100005;
const int mod = 1e9 + 7; 

int main(){
	string s; cin >> s;
	vector<pi> v;
	for(int i=0; i<sz(s); ){
		int e = i;
		while(e < sz(s) && s[i] == s[e]) e++;
		v.emplace_back(s[i], e - i);
		i = e;
	}
	for(int i=0; i<sz(v); i++){
		if(v[i].first != v[sz(v) - i - 1].first){
			puts("0");
			return 0;
		}
		if(v[i].second + v[sz(v) - i - 1].second <= 2){
			puts("0");
			return 0;
		}
	}
	assert(sz(v) % 2 == 1);
	int ans = v[sz(v) / 2].second + 1;
	if(ans <= 2) ans = 0;
	cout << ans << endl;
}
