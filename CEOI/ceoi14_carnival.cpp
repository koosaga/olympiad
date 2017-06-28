#include <bits/stdc++.h>
using namespace std;
 
int party(set<int> s){
	printf("%d\n", s.size());
	fflush(stdout);
	for(auto &i : s) printf("%d ", i);
	fflush(stdout);
	int ret;
	scanf("%d",&ret);
	return ret;
}
 
void findClothes(int N, vector<int> &C)
{
	int size[151] = {};
	int piv = 0;
	set<int> s;
	for(int i=1; i<=N; i++){
		s.insert(i);
		size[i] = party(s);
		if(size[i] == size[i-1]){
			int s = 1, e = i-1;
			while (s != e) {
				int m = (s+e)/2;
				set<int> original;
				for (int i=s; i<=m; i++) {
					original.insert(i);
				}
				int v = party(original);
				original.insert(i);
				if(v != party(original)) s = m+1;
				else e = m;
			}
			C.push_back(C[e-1]);
		}
		else{
			C.push_back(++piv);
		}
	}
}
 
int main(){
	int n; cin >> n;
	vector<int> v;
	findClothes(n, v);
	printf("0\n");
	for(auto &i : v) printf("%d ", i);
}
