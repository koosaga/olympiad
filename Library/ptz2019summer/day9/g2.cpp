#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
using pi = pair<int, int>;
using lint = long long;
#define sz(v) ((int)(v).size())

int main(){
	double ret = -1;
	int pos = -1;
	for(int i=0; i<3; i++){
		int x, y; cin >> x >> y;
		x *= 10; y *= 10;
		if(x >= 5000) x -= 500;
		if(ret < 1.0 *y/ x){
			ret = 1.0 * y / x;
			pos = i;
		}
	}
	cout << "SNU"[pos] << endl;
}
