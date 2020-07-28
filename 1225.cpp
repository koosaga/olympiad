// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1225
#include <bits/stdc++.h>
using namespace std;
int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	int n;
	while(cin >> n){
		int resp = -1, total = 0;
		vector<int> v;
		for(int i = 0;i<n;i++){
			int x;
			cin >> x;
			total += x;
			v.push_back(x);
		}
		if(total % n != 0){
			cout << resp << endl;
			continue;
		}
		resp = 0;
		total /= n;
		for(int i = 0;i<n;i++){
			resp += abs(v[i] - total);
		}
		cout << resp/2 + 1 << endl;
	}
	return 0;
}
