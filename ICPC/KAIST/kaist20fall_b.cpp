#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 18;
using lint = long long;
using pi = pair<int, int>;

int main(){
	int a, b, c; cin >> a >> b >> c;
	c = (c + 4) / 5;
	if(b < c){
		puts("1");
		return 0;
	}
	double p = 1;
	for(int i=0; i<c; i++){
		p *= (b - i);
		p /= (a - i);
	}
	printf("%.10f\n", 1 - p);
}
