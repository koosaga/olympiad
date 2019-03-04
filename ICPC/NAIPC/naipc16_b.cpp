#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 7;

string s;
int mat[4005], zarisu[1000005];

string stamp(int s, int e){
	char buf[50] = "";
	sprintf(buf, "%d,%d:", s, e);
	string ans = buf;
	return ans;
}

short dp[4005][25000];
short nz[4005][25000];

int f(int s, int e, int idx){
	if(s > e) return 0;
	if(mat[s] == e){
		if(dp[s][idx]) return dp[s][idx];
		int z = zarisu[idx] * 2 + 2;
		while(1){
			int l = f(s+1, e-1, idx + z);
			int stp = idx + z;
			int edp = idx + z + l;
			if(zarisu[stp] + zarisu[edp] + 2 > z) z = zarisu[stp] + zarisu[edp] + 2;
			else{
				nz[s][idx] = z;
				return dp[s][idx] = z + l;
			}
		}
	}
	else{
		int l = f(s, mat[s], idx);
		int r = f(mat[s] + 1, e, idx + l);
		return l + r;
	}
}

string construct(int s, int e, int idx){
	if(s > e) return "";
	if(mat[s] == e){
		int z = nz[s][idx];
		auto l = construct(s+1, e-1, idx + z);
		int stp = idx + z;
		int edp = idx + z + l.size();
		return stamp(stp, edp) + l;
	}
	else{
		string l = construct(s, mat[s], idx);
		string r = construct(mat[s] + 1, e, idx + l.size());
		return l + r;
	}
}

int main(){
	for(int i=0; i<10; i++) zarisu[i] = 1;
	for(int i=10; i<100; i++) zarisu[i] = 2;
	for(int i=100; i<1000; i++) zarisu[i] = 3;
	for(int i=1000; i<10000; i++) zarisu[i] = 4;
	for(int i=10000; i<100000; i++) zarisu[i] = 5;
	for(int i=100000; i<1000000; i++) zarisu[i] = 6;
	cin >> s;
	stack<int> stk;
	for(int i=0; i<s.size(); i++){
		if(s[i] == '(') stk.push(i);
		else{
			mat[stk.top()] = i;
			stk.pop();
		}
	}
	f(0, s.size() - 1, 0);
	cout << construct(0, s.size() - 1, 0) << endl;
}
