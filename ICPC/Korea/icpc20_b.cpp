#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3005;

int a[6], b[6];

int main(){
	for(int i=0; i<6; i++) cin >> a[i];
	for(int i=0; i<6; i++) cin >> b[i];
	int cnt = 0;
	for(int i=0; i<6; i++){
		for(int j=0; j<6; j++){
			if(a[i] > b[j]) cnt++;
		}
	}
	int g = gcd(36, cnt);
	cnt /= g;
	int dnt = 36 / g;
	printf("%d/%d\n", cnt, dnt);
}
