#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int n, m;

string bin(int x, int n){
	string ans;
	for(int i=n-1; i>=0; i--){
		ans.push_back((x >> i) % 2 + '0');
	}
	return ans;
}

int main(){
	cin >> m;
	while((1 << n) < m) n++;
	int left = (1 << n) - m;
	for(int i=0; i<left; i++){
		puts(bin(i, n - 1).c_str());
	}
	for(int i=2*left; i<(1<<n); i++){
		puts(bin(i, n).c_str());
	}
}
