#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
 
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
 
 
int main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0); cout.tie(0);
	int Q;
	cin >> Q;
	while(Q--){
		int n, m; cin >> n >> m;
		auto scan = [&](int x, int y) {
			cout << "SCAN " << x << " " << y << endl;
			int z;
			cin >> z;
			return z;
		};
		int rd1 = scan(1, 1);
		int rd2 = scan(1, m);
		int cx = (rd1 + rd2) - 2 * m + 2;
		cx /= 2;
		int sumy = (rd1 - rd2) + 2 + 2 * m;
		sumy /= 2;
		int rd3 = scan(1, sumy / 2);
		int deltay = rd3 - cx; // now we know y coordinate
		int sumx = cx + 2;
		int rd4 = scan(sumx / 2, sumy / 2);
		int deltax = rd4 - deltay;
		int x1 = (sumx - deltax) / 2;
		int x2 = (sumx + deltax) / 2;
		int y1 = (sumy - deltay) / 2;
		int y2 = (sumy + deltay) / 2;
		cout << "DIG " << x1 << " " << y1 << endl;
		int z; cin >> z;
		if(z == 0) {
			cout << "DIG " << x2 << " " << y1 << endl;
			cin >> z; assert(z == 1);
			cout << "DIG " << x1 << " " << y2 << endl;
			cin >> z; assert(z == 1);
		}
		else {
			cout << "DIG " << x2 << " " << y2 << endl;
			cin >> z;
			assert(z == 1);
		}
	}
}
