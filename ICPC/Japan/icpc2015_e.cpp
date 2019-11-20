#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 1005;
const int inf = 1e9 + 100;

string s;
int ins = 0; 
lint inp = 1;

unordered_map<lint, lint> mp[15][15 * 9][2][2];

lint f(int l, int sum, lint prod, int lower, int upper){
	if(sum > ins) return 0;
	if(l == sz(s)){
		if(make_tuple(sum, prod, -lower) 
			<= make_tuple(ins, inp, -1)) return 1;
		return 0;
	}
	if(mp[l][sum][lower][upper].find(prod) != mp[l][sum][lower][upper].end()){
		return mp[l][sum][lower][upper][prod];
	}
	lint ret = 0;
	for(int i = 0; i <= 9; i++){
		int nlower = (lower || (!upper && i < (s[l] - '0')));
		int nupper = (upper || (!lower && i > (s[l] - '0')));
		ret += f(l + 1, sum + i, prod * (i + 1), nlower, nupper); 
	}
	return mp[l][sum][lower][upper][prod] = ret;
}

int main(){
	cin >> s;
	for(auto &i : s){
		ins = ins + i - '0';
		inp = inp * (i - '0' + 1
		);
	}
	cout << f(0, 0, 1, 0, 0) << endl;
}
