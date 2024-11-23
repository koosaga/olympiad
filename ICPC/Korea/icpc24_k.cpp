#include <bits/stdc++.h>
using namespace std;

int nxt[3010000][26];

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	string S;
	cin >> S;
	reverse(S.begin(), S.end());
	int N = (int)S.size();
	// vector<vector<int> > nxt(N+1, vector<int>(26, N+1));
	for(int i = 0; i < 26; i++){
		nxt[N][i] = N+1;
	}
	for(int i = N-1; i >= 0; i--){
		for(int j = 0; j < 26; j++){
			nxt[i][j] = nxt[i+1][j];
		}
		nxt[i][S[i]-'a'] = i+1;
	}
	queue<int> q;
	vector<int> dist(N+1, -1);
	q.push(0);
	dist[0] = 0;
	while(!q.empty()){
		int v = q.front(); q.pop();
		for(int j = 0; j < 26; j++){
			if(nxt[v][j] == N+1) continue;
			int w = nxt[v][j];
			if(dist[w] == -1){
				dist[w] = dist[v] + 1;
				q.push(w);
			}
		}
	}
	int ans = *max_element(dist.begin(), dist.end());
	cout << ans << '\n';
}
