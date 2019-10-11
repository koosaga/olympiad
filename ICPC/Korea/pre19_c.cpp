#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
#define sz(v) ((int)(v).size())
using lint = long long;

int n, a[100];
lint w;

int main(){
	cin >> n >> w;
	for(int i=0; i<n; i++){
		cin >> a[i];
	}
	for(int i=1; i<n; i++){
		if(a[i] > a[i-1]){
			lint del = w / a[i-1];
			w %= a[i-1];
			w += del * a[i];
		}
	}
	cout << w << endl;
}
