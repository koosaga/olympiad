// Ivan Carvalho
// Solution to https://dmoj.ca/problem/cco18p4
#include <bits/stdc++.h>
using namespace std;

int func(int x,int y){
	cout << "? " << x << " " << y << endl;
	int ans;
	cin >> ans;
	return ans; 
}

int main(){
	int R,C,K;
	cin >> R >> C >> K;
	int x_lo = 1, x_hi = R,y_lo = 1,y_hi = C,x_mid,y_mid;
	while(x_lo != x_hi || y_lo != y_hi){
		x_mid = (x_lo+x_hi)/2;
		y_mid = (y_lo+y_hi)/2;
		int v1 = func(x_mid,y_mid),v2;
		if(x_lo != x_hi) v2 = func(x_mid+1,y_mid);
		else v2 = 2*1e9 + 10;
		if(v1 < v2){
			x_hi = x_mid;
		}
		else if(v1 == v2){
			x_lo = x_mid;
			x_hi = x_mid;
		}
		else{
			x_lo = x_mid + (x_lo + 1 == x_hi);
		}
		if(y_lo != y_hi){
			int v3 = func(x_mid,y_mid+1);
			if(v1 < v3){
				y_hi = y_mid;
			}
			else if(v1 == v3){
				y_lo = y_mid;
				y_hi = y_mid;
			}
			else{
				y_lo = y_mid + (y_lo + 1 == y_hi);
			}
		}
	}
	cout << "! " << func(x_lo,y_lo) << endl;
	return 0;
}
