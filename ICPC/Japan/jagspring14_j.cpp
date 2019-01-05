#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int n, a, b;

int main(){
	int nimv = 0;
	scanf("%d %d %d",&n,&a,&b);
	if(a == b){
		for(int i=0; i<n; i++){
			int x; scanf("%d",&x);
			x %= (a + 1);
			nimv ^= x;
		}
	}
	if(a > b){
		for(int i=0; i<n; i++){
			int x; scanf("%d",&x);
			if(x > b){
				puts("Hanako");
				return 0;
			}
			nimv ^= x;
		}
	}
	if(a < b){
		vector<int> v;
		for(int i=0; i<n; i++){
			int x; scanf("%d",&x);
			if(x > a) v.push_back(x);
			else nimv ^= x;
		}
		if(v.size() > 1){
			puts("Jiro");
			return 0;
		}
		if(v.size() == 1){
			if(v[0] - a <= nimv && nimv <= v[0] - 1 && nimv <= a){
				puts("Hanako");
				return 0;
			}
			puts("Jiro");
			return 0;
		}
	}
	puts(nimv ? "Hanako" : "Jiro");
}

