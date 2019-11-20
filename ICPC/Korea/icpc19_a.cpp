#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1005;
const int inf = 1e9 + 100;

int n;
int A[MAXN];

bool bad(int x){
	for(int i=1; x-2*i>=0; i++){
		if(A[x] - A[x-i] == A[x-i] - A[x-2*i]) return 1;
	}
	return 0;
}

int main(){
	A[0] = A[1] = 1;
	cin >> n;
	for(int i=2; i<=n; i++){
		A[i] = 1;
		while(bad(i)) A[i]++;
	}
	cout << A[n] << endl;
}
