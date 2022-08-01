#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int s, w, k;
	cin >> s >> w >> k;
	double d = 0;
	while(true){
		int delta = (w % k ? w % k : k);
		int bunmo = 2 * ((w - delta) / k) + 1;
		if(d + 1.0 * delta / bunmo >= s){
			printf("%.3f\n", w - (s - d) * bunmo);
			return 0;
		}
		else{
			w -= delta;
			d += 1.0 * delta / bunmo;
		}
	}
}
