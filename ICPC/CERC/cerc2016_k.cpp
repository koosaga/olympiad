#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
char str[300005];

int main(){
	scanf("%s", str);
	n = strlen(str);
	vector<int> v;
	for(int i=0; i<n; i+=3){
		if(i + 3 == n){
			if(str[i] == str[i+1] && str[i+1] == str[i+2]){
				v.push_back(i+1);
			}
			break;
		}
		int nxt = -1;
		int cnt = 0;
		if(str[i] != str[i+1]) cnt++;
		if(str[i+1] != str[i+2]) cnt++;
		if(str[i+2] != str[i+3]) cnt++;
		if(cnt == 0){
			nxt = i+1;
		}
		if(cnt == 1){
			if(str[i] != str[i+1]){
				nxt = i+2;
			}
			if(str[i+1] != str[i+2]){
				nxt = i+1;
			}
			if(str[i+2] != str[i+3]){
				nxt = i+2;
			}
		}
		if(nxt != -1){
			str[nxt] ^= 1;
			str[nxt+1] ^= 1;
			v.push_back(nxt);
		}
	}
	printf("%d\n", v.size());
	for(auto &i : v) printf("%d ", i+1);
}
