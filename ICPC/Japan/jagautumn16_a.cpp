#include <bits/stdc++.h>
using namespace std;
using lint = long long;

int solve(int x){
	vector<int> vec;
	int ret = x;
	while(x){
		vec.push_back(x % 10);
		x /= 10;
	}
	reverse(vec.begin(), vec.end());
	for(int i=1; i<vec.size(); i++){
		if(vec[i-1] + 1 != vec[i]) return -1;
	}
	return ret;
}

int n, a[1005];
int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i];
	int ret = -1;
	for(int i=0; i<n; i++) for(int j=0; j<i; j++) ret = max(ret, solve(a[i] * a[j]));
	cout << ret << endl;
}
