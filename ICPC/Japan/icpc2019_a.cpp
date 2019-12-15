#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;

int f(lint n){
	if(n <= 4) return n;
	if(n % 3 != 2) return f(n - 1) + 1;
	return f(n / 3) + 2;
}

int main(){
	lint x; cin >> x; cout << f(x+1)-1 << endl;
}

