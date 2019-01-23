#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;

char str[222222];

int main(){
	int n; cin >> n;
	int l = 1;
	while(l * (l + 1) / 2 < n) l++;
	for(int i=0; i<l; i++) str[i] = ')', str[i + l] = '(';
	int eudori = l * (l + 1) / 2 - n;
	for(int i=l; i<l+l; i++){
		for(int j=i; j; j--){
			if(eudori == 0){
				puts(str);
				return 0;
			}
			if(str[j-1] == ')' && str[j] == '('){
				swap(str[j-1], str[j]);
				eudori--;
			}
		}
	}
}
