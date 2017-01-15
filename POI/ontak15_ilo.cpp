#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;

const llf eps = 1e-12;

int n;
int a[105][105];
llf x[105], y[105];

vector<llf> basis[105];
llf dap[105];

void insert(vector<llf> &v, llf ans){
	for(int i=0; i<n-1; i++){
		if(fabs(v[i]) > eps){
			if(!basis[i].size()){
				basis[i] = v;
				dap[i] = ans;
				return;
			}
			for(int j=i; j<n-1; j++){
				v[j] -= (v[i] * basis[i][j]) / basis[i][i];
			}
			ans -= (v[i] * dap[i]) / basis[i][i];
		}
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			cin >> a[i][j];
		}
	}
	x[0] = 1, y[0] = 0;
	for(int i=1; i<n; i++){
		y[i] = a[0][i];
	}
	for(int i=1; i<n; i++){
		for(int j=1; j<i; j++){
			vector<llf> v(n-1);
			v[j-1] = -y[i];
			v[i-1] = y[j];
			insert(v, a[i][j]);
		}
	}
	for(int i=n-2; i>=0; i--){
		if(basis[i].size()){
			for(int j=i+1; j<n; j++){
				dap[i] -= basis[i][j] * dap[j];
			}
			dap[i] /= basis[i][i];
		}
		x[i+1] = dap[i];
	}
	for(int i=0; i<n; i++){
		printf("%.20Lf %.20Lf\n", x[i], y[i]);
	}
}
