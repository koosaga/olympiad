#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

char buf[100];
int N;

string swap(int x, int y){
	x++; y++;
	if(y > N) return "";
	sprintf(buf, "CMPSWP R%d R%d ", x, y);
	string ret = buf;
	return ret;
}

int main(){
	int n; cin >> n;
	N = n;
	while(n != (n & -n)) n += (n & -n);
	vector<string> buf;
	for(int step = 2; step <= n; step <<= 1){
		string ans;
		for(int j = 0; j < n; j += step){
			for(int k = 0; k < step / 2; k++){
				ans += swap(j + k, j + step - k - 1);
			}
		}
		if(sz(ans)) buf.push_back(ans);
		for(int j = step / 4; j >= 1; j >>= 1){
			string ans;
			for(int k = 0; k < n; k++){
				if((j & k) == 0) ans += swap(k, k + j);
			}
		if(sz(ans)) buf.push_back(ans);
		}
	}
	printf("%d\n", sz(buf));
	for(auto &s : buf) puts(s.c_str());
}


