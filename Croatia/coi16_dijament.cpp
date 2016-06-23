#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, p;
map<string, int> mp;
 
bitset<1005> prec[1005], gph[1005], rev[1005];
 
bool solve(int x, bitset<1005> &v){
	for(int i=1; i<=p; i++){
		if(!v[i]) continue;
		auto t = prec[i] & ~gph[i];
		if((t & v).any()){
			return 0;
		}
	}
	return 1;
}
 
int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		string t, b;
		cin >> t >> b;
		if(mp.find(t) != mp.end()){
			puts("greska");
			while(1){
				cin >> b;
				if(b == ";") break;
			}
			continue;
		}
		bitset<1005> v;
		bool bad = 0;
		while(1){
			string x;
			cin >> x;
			if(x == ";") break;
			if(mp.find(x) == mp.end()){
				bad = 1;
			}
			else{
				v[mp[x]] = true;
			}
		}
		if(bad || solve(p+1, v) == false){
			puts("greska");
		}
		else{
			puts("ok");
			p++;
			mp[t] = p;
			for(int i=1; i<p; i++){
				if(v[i]){
					v |= gph[i];
				}
			}
			for(int i=1; i<p; i++){
				if(v[i]){
					prec[p] |= rev[i];
				}
			}
			for(int i=1; i<p; i++){
				if(v[i]){
					rev[i][p] = true;
				}
			}
			gph[p] = v;
		}
	}
}
