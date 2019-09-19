#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4005;
using lint = long long;

int main(){
	lint n;
	cin >> n;
	set<lint> s;
	s.insert(n);
	vector<pair<lint, lint>> ord;
	while(s.size()){
		lint n = *s.rbegin();
		s.erase(n);
		if(n > 2){
			lint e = 2e9;
			{
				lint s = 0;
				while(s != e){
					lint m = (s+e)/2;
					if(m * m >= n) e = m;
					else s = m + 1;
				}
			}
			ord.emplace_back(e, e*e - n);
			s.insert(e);
			s.insert(e*e - n);
		}
	}
	reverse(ord.begin(), ord.end());
	for(auto &i : ord) printf("%lld %lld\n", i.first, i.second);
}
