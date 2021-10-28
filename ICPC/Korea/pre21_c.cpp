#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
using point = complex<llf>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 30;

int n;
string s[MAXN];
int k[MAXN];

bool match(lint k, string s){
	if(s == "G") return 1;
	if(s == "R") return k % 2 == 1;
	return k % 2 == 0;
}

int main(){
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		cin >> s[i] >> k[i];
		if(k[i] == 1) s[i] = "G";
	}
	lint ret = 0;
	lint toMove = 1;
	for(int i = n - 1; i >= 0; i--){
		if(match(toMove, s[i]) == 0){
			ret += k[i] * (toMove + 1) - (i == 0);
			toMove = toMove * 2 + 1;
		}
		else {
			ret += k[i] * toMove;
			toMove = toMove * 2;
		}
	}
	cout << ret << endl;
}

