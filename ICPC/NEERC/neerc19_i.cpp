// shirley smokes weed
#include <bits/stdc++.h>
#define sz(v) ((lint)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int a[10];
int b[10][10];

bool le(int x, int y){
	//b[max(a[x], a[y])][min(a[x], a[y])] = 1;
	//return a[x] < a[y];
	cout << "? " << x+1 << " " << y + 1 << endl;
	char c[5]; cin >> c;
	return c[0] == '<';
}

int getN(){
	int n; cin >> n; return n;
}

void Do(){
	int n = getN();
	vector<int> v, w;
	if(n == 3){
		vector<pi> v;
		for(int i=0; i<n; i++){
			if(le(2*i, 2*i+1)) v.emplace_back(2*i+1, 2*i);
			else v.emplace_back(2*i, 2*i+1);
		}
		if(le(v[0].second, v[1].second)) v[0].second = -1;
		else v[1].second = -1;
		int pos = (v[0].second == -1 ? 1 : 0);
		if(le(v[pos].second, v[2].second)) v[pos].second = -1;
		else v[2].second = -1;
		for(int i=0; i<3; i++){
			if(v[i].second != -1){
				vector<int> c1 = {v[i].first, v[i].second};
				vector<int> c2;
				for(int j=0; j<3; j++){
					if(i != j) c2.push_back(v[j].first);
				}
				if(le(c2[0], c2[1])) swap(c2[0], c2[1]);
				le(c2[1], c1[1]);
				break;
			}
		}
		cout << "!" << endl;
		return;
	}
	for(int i=0; i<n-1; i++){
		v.push_back(2+i);
		w.push_back(n+1+i);
	}
	for(int i=1; i<sz(v); i++){
		for(int j=i-1; j>=0; j--){
			if(le(v[j], v[j+1])){
				swap(v[j], v[j+1]);
			}
			else break;
		}
	}
	for(int i=1; i<sz(w); i++){
		for(int j=i-1; j>=0; j--){
			if(le(w[j], w[j+1])){
				swap(w[j], w[j+1]);
			}
			else break;
		}
	}
	for(int i=0; i<n-2; i++){
		if(le(v.back(), w.back())) v.pop_back();
		else w.pop_back();
	}
	for(int i=0; i<2; i++){
		if(sz(v) < sz(w)) swap(v, w);
		w.push_back(i);
		for(int i=sz(w)-2; i>=0; i--){
			if(le(w[i], w[i+1])) swap(w[i], w[i+1]);
			else break;
		}
	}
	for(int i=0; i<2; i++){
		if(le(v.back(), w.back())) v.pop_back();
		else w.pop_back();
	}
	cout << "!" << endl;
}

int main(){
	/*
	int n = getN();
	iota(a, a + n+n, 0);
	do{
		Do();
		for(int i=0; i<2*n; i++){
			for(int j=0; j<2*n; j++){
				for(int k=0; k<2*n; k++){
					b[j][k] |= (b[j][i] & b[i][k]);
				}
			}
		}
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(!b[j+n][i]){
					puts("no big");
					exit(0);
				}
			}
		}
		bool good = 0;
		for(int i=0; i<n; i++){
			for(int j=0; j<i; j++){
				if(!b[i+n][j+n]) good = 1;
			}
		}
		if(!good){
			puts("no good");
			exit(0);
		}
		memset(b, 0, sizeof(b));
	}while(next_permutation(a, a + n+n));
	return 0;*/
	int t; cin >> t;
	while(t--) Do();
}
