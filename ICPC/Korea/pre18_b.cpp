#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;

int main(){
	int a, b, n, w;
	cin >> a >> b >> n >> w;
	int cnt = 0;
	for(int i=1; i<n; i++){
		if(a*i+b*(n-i) == w){
			cnt++;
		}
	}
	if(cnt != 1){
		puts("-1");
		return 0;
	}
	for(int i=1; i<n; i++){
		if(a*i+b*(n-i) == w){
			cout << i << " " << n - i << endl;
			return 0;
		}
	}
}
