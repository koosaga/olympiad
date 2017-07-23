namespace stable_marriage{
	vector<vector<int>> rev; // 0-based
	vector<int> solve(int n, vector<vector<int>> &a, vector<vector<int>> &b){
		rev.clear(); rev.resize(n, vector<int>(n, 0));
		vector<int> ret(n), pnt(n), mat(n, -1);
		queue<int> que;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++) rev[i][b[i][j]] = j;
			que.push(i);
		}
		while(!que.empty()){
			int x = que.front(); que.pop();
			int y = a[x][pnt[x]++];
			if(mat[y] == -1) mat[y] = x, ret[x] = y;
			else{
				if(rev[y][mat[y]] > rev[y][x]){
					que.push(mat[y]);
					mat[y] = x, ret[x] = y;
				}
				else que.push(x);
			}
		}
		return ret; // optimal matching of A side (x)
	}
};