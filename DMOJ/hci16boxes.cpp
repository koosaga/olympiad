// Ivan Carvalho
// Solution to https://dmoj.ca/problem/hci16boxes
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
vector<ii> sweep,atu;
int bit[MAXN];
void update(int idx,int val){
	while(idx < MAXN){
		bit[idx] = max(bit[idx],val);
		idx += LSOne(idx);
	}
}
int read(int idx){
	int ans = 0;
	while(idx > 0){
		ans = max(ans,bit[idx]);
		idx -= LSOne(idx);
	}
	return ans;
}
int main(){
	int n;
	cin >> n;
	for(int i = 1;i<=n;i++){
		int x,y;
		cin >> x >> y;
		sweep.push_back(ii(x,y));
	}
	sort(sweep.begin(),sweep.end());
	for(int  i = 0;i < n;i++){
		int x = sweep[i].first;
		int y = sweep[i].second;
		if(i >= 1 && sweep[i-1].first != x){
			while(!atu.empty()){
				update(atu.back().first,atu.back().second);
				atu.pop_back();
			}
		}
		atu.push_back(ii(y, read(y - 1) + 1 ));
	}
	while(!atu.empty()){
		update(atu.back().first,atu.back().second);
		atu.pop_back();
	}
	cout << read(MAXN - 1) << endl;
	return 0;
}