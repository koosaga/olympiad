#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55;
using pi = pair<int, int>;

int n, q;
char a[MAXN][15];
vector<pi> ord = {pi(4, 6), pi(2, 8), pi(0, 10), pi(5, 5), pi(1, 9)};

int f(int r){
	int ans = 0;
	for(int i=0; i<11; i++){
		if(a[r][i] == '-') ans++;
	}
	return ans;
}

int mindist(int x){
	return min({abs(x), abs(x - n/2 - 1), abs(x - n - 2)});
}

int cnt(int l, int r){
	int ans = 0;
	for(int i=0; i<n+3; i++){
		for(int j=l; j<=r; j++){
			if(a[i][j] == '-') ans++;
		}
	}
	return ans;
}

void assign_passenger(int r, char c){
	for(auto &i : ord){
		if(a[r][i.first] != '-' && a[r][i.second] != '-'){
			continue;
		}
		if(a[r][i.first] != '-') a[r][i.second] = c;
		else if(a[r][i.second] != '-') a[r][i.first] = c;
		else{
			if(cnt(0, 4) < cnt(6, 10)) a[r][i.second] = c;
			else a[r][i.first] = c;
		}
		return;
	}
	assert(0);
}

int main(){
	cin >> n >> q;
	vector<int> v;
	for(int i=0; i<n+3; i++) cin >> a[i], v.push_back(i);
	for(int i=0; i<q; i++){
		char ret = i + 'a';
		if(f(1) || f(n/2+2)){
			vector<int> v = {1, n/2+2};
			assign_passenger(*max_element(v.begin(), v.end(), [&](const int &a, const int &b){
				if(f(a) != f(b)) return f(a) < f(b);
				else return mindist(a) > mindist(b);
			}), ret);
		}
		else{
			vector<int> v(n+3);
			iota(v.begin(), v.end(), 0);
			assign_passenger(*max_element(v.begin(), v.end(), [&](const int &a, const int &b){
				if(f(a) != f(b)) return f(a) < f(b);
				else return mindist(a) > mindist(b);
			}), ret);
		}
	}
	for(int i=0; i<n+3; i++) cout << a[i] << endl;
}

