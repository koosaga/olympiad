#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
 
int n;
 
char buf[MAXN];
 
int main(){
	scanf("%d",&n);
	vector<pi> cnd;
	for(int i=1; i<=n; i++){
		lint b, d; cin >> b >> d;
		cout << (b - 1) / (d / gcd(b, d)) << endl;
	}
}
 
