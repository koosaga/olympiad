// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi16p4
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2*1e5 + 10;
const int MAXK = 101;

int V[MAXN],Black[MAXN],White[MAXN];
int dp[MAXN][MAXK][2],block_sz[MAXN],pref_sum[MAXN],N,K;

int valid(int a,int b){
	if(max(a,b) > N) return 0;
	return (b - a + 1) == (pref_sum[b] - pref_sum[a-1]);
}

void add(int a,int b){
	Black[a]++;
	Black[b+1]--;
}

int solve(int pos,int k,int naopode){
	
	if(k == -1) return 0;

	int &ret = dp[pos][k][naopode];

	if(dp[pos][k][naopode] != -1) return ret;

	ret = 0;

	if(pos == N + 1){
		if(k == 0){
			ret = 1;
		}
		else{
			ret = 0;
		}
		return ret;
	}

	if(naopode){
		if(V[pos] == 0 || V[pos] == 1){
			if(solve(pos+1,k,0)){
				White[pos]++;
				ret = 1;
			}
			return ret;
		}
		else if(V[pos] == 2){
			ret = 0;
			return ret;
		}
	}

	if(V[pos] == 0 || V[pos] == 1){
		if(solve(pos+1,k,0)){
			White[pos]++;
			ret = 1;
		}
	}
	if(V[pos] == 0 || V[pos] == 2){
		if(valid(pos, pos + block_sz[k] - 1 ) &&  solve(pos + block_sz[k],k - 1,1)){
			add(pos, pos + block_sz[k] - 1 );
			ret = 1;
		}
	}

	return ret;

}

string solve_puzzle(string s, int k, int c[]){

	N = s.size();
	K = k;

	memset(dp,-1,sizeof(dp));
	for(int i = K,j = 0;j<k;i--,j++){
		block_sz[i] = c[j];
	}

	for(int i = 1;i<=N;i++){
		if(s[i-1] == '.'){
			pref_sum[i] = pref_sum[i-1] + 1;
			V[i] = 0;
		}
		else if(s[i-1] == 'X'){
			pref_sum[i] = pref_sum[i-1] + 1;
			V[i] = 2;
		}
		else{
			pref_sum[i] = pref_sum[i-1];
			V[i] = 1;
		}
	}

	solve(1,K,0);

	string ans;
	for(int i = 1;i<=N;i++){
		Black[i] += Black[i-1];
		if(Black[i] > 0 && White[i] > 0){
			ans.push_back('?');
		}
		else if(White[i] > 0){
			ans.push_back('_');
		}
		else{
			ans.push_back('X');
		}
	}

	return ans;

}

int main(){

	string si;
	int ki,ci[MAXN];
	cin >> si;
	cin >> ki;
	for(int i = 0;i<ki;i++) cin >> ci[i];
	cout << solve_puzzle(si,ki,ci) << endl;

	return 0;
}