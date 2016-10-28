#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
bitset<205> basis[205];
bool sol[205];

void insert(bitset<205> v, int s){
	for(int i=0; i<n; i++){
		if(v[i]){
			if(!basis[i][i]){
				basis[i] = v;
				sol[i] = s;
				return;
			}
			else{
				v ^= basis[i];
				s ^= sol[i];
			}
		}
	}
	if(s){
		puts("-1");
		exit(0);
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		int x, y;
		scanf("%d",&x);
		bitset<205> rw;
		for(int j=0; j<x; j++){
			scanf("%d",&y);
			rw[y-1] = 1;
		}
		if(x % 2 == 0){
			insert(rw, 0);
		}
		else{
			rw[i] = 1;
			insert(rw, 1);
		}
	}
	for(int i=n-1; i>=0; i--){
		if(basis[i][i]){
			for(int j=i+1; j<n; j++){
				if(sol[j] & basis[i][j]){
					sol[i] ^= 1;
				}
			}
		}
	}
	vector<int> v;
	for(int i=0; i<n; i++){
		if(sol[i]) v.push_back(i+1);
	}
	printf("%d\n", v.size());
	for(int i=0; i<v.size(); i++) printf("%d ", v[i]);
}

