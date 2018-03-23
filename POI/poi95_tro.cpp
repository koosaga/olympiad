#include <bits/stdc++.h>
using namespace std;

vector<int> v;

int main(){
	while(true){
		int n;
		scanf("%d",&n);
		if(n == 0) break;
		v.push_back(n);
	}
	sort(v.begin(), v.end());
	for(int i=0; i+2<v.size(); i++){
		if(v[i] + v[i+1] > v[i+2]){
			printf("%d %d %d\n", v[i], v[i+1], v[i+2]);
			return 0;
		}
	}
	puts("NIE");
}

