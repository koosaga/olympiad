#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int main(){
	int n;
	scanf("%d",&n);
	vector<int> a(1 << n);
	for(auto &i : a) scanf("%d",&i);
	for(int i=0; i<sz(a); i++){
		vector<int> v;
		for(int j = 0; j < n; j++){
			if((i >> j) % 2 == 0) v.push_back(j);
		}
		for(int j = 0; j < sz(v); j++){
			for(int k = 0; k < j; k++){
				if(a[i|(1<<v[j])] + a[i|(1<<v[k])] < 
					a[i] + a[i|(1<<v[j])|(1<<v[k])]){
					printf("%d %d\n", i|(1<<v[j]), i|(1<<v[k]));
					return 0;
				}
			}
		}
	}
	puts("-1");
}