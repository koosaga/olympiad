// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c1p2
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	int x1 = 100,x2 = 1,y1 = 100,y2 = 1;
	while(n--){
		int x,y;
		cin >> x >> y;
		x1 = min(x1,x);
		x2 = max(x2,x);
		y1 = min(y1,y);
		y2 = max(y2,y);
	}
	int delta = max(x2 - x1,y2 - y1);
	cout << delta*delta << endl;
	return 0;
}