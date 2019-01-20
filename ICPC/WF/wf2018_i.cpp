#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXR = 3005;
const int MAXC = 6005;
using lint = long long;

int n, m;
char str[MAXR * 2][MAXC * 2];
int Aux[MAXR][MAXC];
int Up[MAXR][MAXC];
int Dn[MAXR][MAXC];
int Ce[MAXR][MAXC];

struct bit{
	int tree[MAXC];
	void clear() { memset(tree, 0, sizeof(tree)); }
	void add(int x, int v){
		x++;
		while(x < MAXC){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		x++;
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int main(){
	scanf("%d %d\n",&n,&m);
	for(int i=0; i<2*n-1; i++){
		fgets(str[i], MAXC * 2, stdin);
		int l = strlen(str[i]);
		str[i][--l] = 0;
		while(l < 2*m - 1) str[i][l++] = ' ';
	}
	memset(Up, 0x3f, sizeof(Up));
	memset(Dn, 0x3f, sizeof(Dn));
	memset(Ce, 0x3f, sizeof(Ce));
	for(int i=0; i<n; i++){
		int cnt = 0;
		for(int j=0; j<2*m-1; j++){
			if(str[i*2][j] == ' ') cnt = 0;
			else cnt++;
			if(j % 2 == 0) Ce[i][j/2] = min(Ce[i][j/2], cnt / 2);
		}
		cnt = 0;
		for(int j=2*m-2; j>=0; j--){
			if(str[i*2][j] == ' ') cnt = 0;
			else cnt++;
			if(j % 2 == 0) Ce[i][j/2] = min(Ce[i][j/2], cnt / 2);
		}
	}
	auto Good = [&](int x, int y){
		return x >= 0 && x < 2*n-1 && y >= 0 && y < 2*m-1 && str[x][y] != ' ';
	};
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[2*i][2*j] == 'x'){
				Aux[i][j]++;
				if(Good(2*i-1, 2*j-1)) Aux[i][j] += Aux[i-1][j-1];
				Up[i][j] = min(Up[i][j], Aux[i][j] - 1);
			}
		}
	}
	memset(Aux, 0, sizeof(Aux));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[2*i][2*j] == 'x'){
				Aux[i][j]++;
				if(Good(2*i-1, 2*j+1)) Aux[i][j] += Aux[i-1][j+1];
				Up[i][j] = min(Up[i][j], Aux[i][j] - 1);
			}
		}
	}
	memset(Aux, 0, sizeof(Aux));
	for(int i=n-1; i>=0; i--){
		for(int j=0; j<m; j++){
			if(str[2*i][2*j] == 'x'){
				Aux[i][j]++;
				if(Good(2*i+1, 2*j-1)) Aux[i][j] += Aux[i+1][j-1];
				Dn[i][j] = min(Dn[i][j], Aux[i][j] - 1);
			}
		}
	}
	memset(Aux, 0, sizeof(Aux));
	for(int i=n-1; i>=0; i--){
		for(int j=0; j<m; j++){
			if(str[2*i][2*j] == 'x'){
				Aux[i][j]++;
				if(Good(2*i+1, 2*j+1)) Aux[i][j] += Aux[i+1][j+1];
				Dn[i][j] = min(Dn[i][j], Aux[i][j] - 1);
			}
		}
	}
	lint dap = 0;
	for(int j=0; j<m; j++){
		vector<pi> v;
		for(int i=0; i<n; i++) v.emplace_back(i - Ce[i][j], i);
		sort(v.begin(), v.end());
		bit.clear();
		int ptr = 0;
		for(int i=0; i<n; i++){
			if(str[2*i][2*j] == 'x'){
				while(ptr < v.size() && v[ptr].first <= i){
					bit.add(v[ptr++].second, 1);
				}
				dap += bit.query(i + Dn[i][j]) - bit.query(i);
			}
		}
		v.clear();
		bit.clear();
		for(int i=0; i<n; i++) v.emplace_back(i + Ce[i][j], i);
		sort(v.rbegin(), v.rend());
		ptr = 0;
		for(int i=n-1; i>=0; i--){
			if(str[2*i][2*j] == 'x'){
				while(ptr < v.size() && v[ptr].first >= i){
					bit.add(v[ptr++].second, 1);
				}
				dap += bit.query(i - 1) - bit.query(i - Up[i][j] - 1);
			}
		}
	}
	cout << dap << endl;
}
