#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int n, m;

int main(){
	cin >> n >> m;
	int ret = 0;
	for(int i=0; i<n; i++){
		string str;
		cin >> str;
		int open = 0;
		for(int j=0; j<m; j++){
			if(str[j] == '\\'){
				ret += 1;
				open ^= 1;
			}
			if(str[j] == '/'){
				ret += 1;
				open ^= 1;
			}
			if(str[j] == '.'){
				ret += 2 * open;
			}
		}
	}
	cout << ret / 2 << endl;
}
