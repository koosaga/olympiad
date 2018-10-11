#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

vector<int> a, b, c;

int main(){
	int n;
	cin >> n;
	for(int i=0; i<n; i++){
		int x;
		cin >> x;
		if(x < 0) a.push_back(x);
		if(x == 0) b.push_back(x);
		if(x > 0) c.push_back(x);
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());
	while(a.size() > 6) a.erase(a.begin() + 3);
	while(b.size() > 3) b.erase(b.begin() + 3);
	while(c.size() > 6) c.erase(c.begin() + 3);
	vector<int> t;
	for(auto &v : {a, b, c}) for(auto &i : v) t.push_back(i);
	int ret = -2e9;
	for(int i=0; i<t.size(); i++){
		for(int j=i+1; j<t.size(); j++){
			ret = max(ret, t[i] * t[j]);
			for(int k=j+1; k<t.size(); k++) ret = max(ret, t[i] * t[j] * t[k]);
		}
	}
	cout << ret;
}


