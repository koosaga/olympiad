#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;

vector<vector<int>> solve_even(vector<pi> deg){
	queue<int> dtwo, dfour;
	vector<vector<int>> ret;
	for(int i = 0; i < sz(deg); i++){
		if(deg[i].first == 2) dtwo.push(i);
		else dfour.push(i);
	}
	while(sz(dtwo)){
		if(sz(dfour)){
			int x = dfour.front(); dfour.pop();
			int y = dtwo.front(); dtwo.pop();
			int z = dtwo.front(); dtwo.pop();
			vector<int> vect = {x, y, z};
			ret.push_back(vect);
			deg[x].first -= 2;
			if(deg[x].first == 2) dtwo.push(x);
			else dfour.push(x);
		}
		else{
			vector<int> vect;
			while(sz(dtwo)){
				vect.push_back(dtwo.front());
				dtwo.pop();
			}
			ret.push_back(vect);
		}
	}
	for(auto &i : ret) for(auto &j : i) j = deg[j].second;
	return ret;
}

void solve(){
	int n; scanf("%d",&n);
	vector<int> deg(n);
	for(int i=0; i<n; i++) scanf("%d",&deg[i]);
	int sum = accumulate(all(deg), 0);
	if(sum % 2 || sum < 2 * n - 2){
		puts("-1");
		return;
	}
	sum /= 2; sum -= (n - 1);
	if(sum == 0){ // tree case
		queue<int> done, dtwo;
		for(int i=0; i<n; i++){
			if(deg[i] == 1) done.push(i);
			else dtwo.push(i);
		}
		printf("%d\n", n - 1);
		for(int i=0; i<n-1; i++){
			int x = done.front(); done.pop();
			int y;
			if(sz(dtwo)){
				y = dtwo.front(); dtwo.pop();
			}
			else{
				y = done.front(); done.pop();
			}
			printf("2 %d %d\n", x + 1, y + 1);
			deg[y]--;
			if(deg[y] == 1) done.push(y);
			else dtwo.push(y);
		}
		return;
	}
	vector<int> odd;
	int leafCnt = 0;
	for(int i=0; i<n; i++){
		if(deg[i] & 1){
			odd.push_back(i);
			if(deg[i] == 1) leafCnt++;
		}
	}
	sort(all(odd), [&](const int &x, const int &y){
		return deg[x] < deg[y];
	});
	if(sum > (n - 1 - max(sz(odd) / 2, leafCnt)) / 2){
		puts("-1");
		return;
	}
	if(sz(odd) >= 2 * leafCnt){
		vector<pi> evens;
		for(int i=0; i<n; i++){
			if(deg[i] % 2 == 0) evens.emplace_back(deg[i], i);
		}
		vector<pi> labels;
		for(int i=0; i<sz(odd)/2; i++){
			evens.emplace_back(deg[odd[i]] + deg[odd[i + sz(odd) / 2]] - 2, n + i);
			labels.emplace_back(i, deg[odd[i]] / 2);
		}
		vector<vector<int>> cycles = solve_even(evens);	
		for(auto &i : cycles){
			for(auto &j : i){
				if(j >= n){
					if(labels[j - n].second){
						labels[j - n].second--;
						j = labels[j - n].first;
					}
					else{
						j = labels[j - n].first + sz(odd) / 2;
					}
					j = odd[j];
				}
			}
		}
		printf("%d\n", n - 1 + sum);
		for(int i=0; i<sz(odd)/2; i++){
			printf("2 %d %d\n", odd[i] + 1, odd[i + sz(odd) / 2] + 1);
		}
		for(auto &i : cycles){
			for(int j=0; j<sz(i); j++){
				printf("2 %d %d\n", i[j] + 1, i[(j + 1) % sz(i)] + 1);
			}
		}
	}
	else{
		vector<pi> evens;
		for(int i=0; i<n; i++){
			if(deg[i] % 2 == 0) evens.emplace_back(deg[i], i);
		}
		vector<pi> labels;	
		for(int i=0; i<sz(odd) - leafCnt; i++){
			evens.emplace_back(deg[odd[i]] + deg[odd[i + leafCnt]] - 2, n + i);
			labels.emplace_back(i, deg[odd[i]] / 2);
		}
		sort(all(evens));
		reverse(all(evens));
		int ptr = 0;
		vector<tuple<int, int, int>> samjichang;
		for(int i=sz(odd)-leafCnt; i<leafCnt; i+=2){
			samjichang.emplace_back(odd[i], odd[i + 1], evens[ptr].second);
			evens[ptr].first -= 2;
			if(evens[ptr].first == 2) ptr++;
		}
		vector<vector<int>> cycles = solve_even(evens);	
		for(auto &i : cycles){
			for(auto &j : i){
				if(j >= n){
					if(labels[j - n].second){
						labels[j - n].second--;
						j = labels[j - n].first;
					}
					else{
						j = labels[j - n].first + leafCnt;
					}
					j = odd[j];
				}
			}
		}
		printf("%d\n", n - 1 + sum);
		for(auto &[x, y, j] : samjichang){
			if(j >= n){
				if(labels[j - n].second){
					j = labels[j - n].first;
					labels[j - n].second--;
				}
				else{
					j = labels[j - n].first + leafCnt;
				}
				j = odd[j];
			}
			printf("2 %d %d\n", x + 1, j + 1);
			printf("2 %d %d\n", y + 1, j + 1);
		}
		for(int i=0; i<sz(odd) - leafCnt; i++){
			printf("2 %d %d\n", odd[i] + 1, odd[i + leafCnt] + 1);
		}
		for(auto &i : cycles){
			for(int j=0; j<sz(i); j++){
				printf("2 %d %d\n", i[j] + 1, i[(j + 1) % sz(i)] + 1);
			}
		}
	}
}

int main(){
	solve();
}
