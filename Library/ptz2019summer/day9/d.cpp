#include <bits/stdc++.h>
using namespace std;
const int MAXN = 20;
using pi = pair<int, int>;
using lint = long long;
#define sz(v) ((int)(v).size())

int n, a[1 << MAXN], b[1 << MAXN];

int main(){
	scanf("%d",&n);
	vector<int> v(n);
	iota(v.begin(), v.end(), 0);
	int cnt = 0;
	do{
		int good = 1;
		for(int i=0; i<n; i++){
			for(int j=i+1; j<n; j++){
				for(int k=j+1; k<n; k++){
					if(v[i] < v[j] && v[j] < v[k]) good = 0;
				}
			}
		}
		if(good) cnt++;
	}while(next_permutation(v.begin(), v.end()));
	cout << cnt << endl;
}
