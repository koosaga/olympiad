// given simple, nonempty graph
// in O(m log n), returns permutation of vertices (positive) or empty vector (negative) such that
// for p[i], all j > i such that p[j] is adjacent to p[i], constitutes cliques.
// for each undir edge (s, e), both s \in gph[e], e \in gph[s] should hold
vector<int> getPEO(vector<vector<int>> gph){
	int n = sz(gph);
	vector<int> cnt(n), idx(n);
	for(int i=0; i<n; i++) sort(gph[i].begin(), gph[i].end());
	priority_queue<pi> pq;
	for(int i=0; i<n; i++) pq.emplace(cnt[i], i);
	vector<int> ord;
	while(!pq.empty()){
		int x = pq.top().second, y = pq.top().first;
		pq.pop();
		if(cnt[x] != y || idx[x]) continue;
		ord.push_back(x);
		idx[x] = n + 1 - ord.size();
		for(auto &i : gph[x]){
			if(!idx[i]){
				cnt[i]++;
				pq.emplace(cnt[i], i);
			}
		}
	}
	reverse(ord.begin(), ord.end());
	for(auto &i : ord){
		int minBef = 1e9;
		for(auto &j : gph[i]){
			if(idx[j] > idx[i]) minBef = min(minBef, idx[j]);
		}
		minBef--;
		if(minBef < n){
			minBef = ord[minBef];
			for(auto &j : gph[i]){
				if(idx[j] > idx[minBef] && !binary_search(gph[minBef].begin(), gph[minBef].end(), j)){
					return vector<int>();
				}
			}
		}
	}
	return ord;
}