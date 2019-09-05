int n, m, q;
int st[MAXN], ed[MAXN], cost[MAXN], chk[MAXN];
pi qr[MAXN];

bool cmp(int &a, int &b){ return pi(cost[a], a) < pi(cost[b], b); }

void contract(int s, int e, vector<int> v, vector<int> &must_mst, vector<int> &maybe_mst){
	sort(v.begin(), v.end(), cmp);
	vector<pi> snapshot;
	for(int i=s; i<=e; i++) disj.uni(st[qr[i].first], ed[qr[i].first], snapshot);
	for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) must_mst.push_back(i);
	disj.revert(snapshot);
	for(auto &i : must_mst) disj.uni(st[i], ed[i], snapshot);
	for(auto &i : v) if(disj.uni(st[i], ed[i], snapshot)) maybe_mst.push_back(i);
	disj.revert(snapshot);
}

void solve(int s, int e, vector<int> v, lint cv){
	if(s == e){
		cost[qr[s].first] = qr[s].second;
		if(st[qr[s].first] == ed[qr[s].first]){
			printf("%lld\n", cv);
			return;
		}
		int minv = qr[s].second;
		for(auto &i : v) minv = min(minv, cost[i]);
		printf("%lld\n",minv + cv);
		return;
	}
	int m = (s+e)/2;
	vector<int> lv = v, rv = v;
	vector<int> must_mst, maybe_mst;
	for(int i=m+1; i<=e; i++){
		chk[qr[i].first]--;
		if(chk[qr[i].first] == 0) lv.push_back(qr[i].first);
	}
	vector<pi> snapshot;
	contract(s, m, lv, must_mst, maybe_mst);
	lint lcv = cv;
	for(auto &i : must_mst) lcv += cost[i], disj.uni(st[i], ed[i], snapshot);
	solve(s, m, maybe_mst, lcv);
	disj.revert(snapshot);
	must_mst.clear(); maybe_mst.clear();
	for(int i=m+1; i<=e; i++) chk[qr[i].first]++;
	for(int i=s; i<=m; i++){
		chk[qr[i].first]--;
		if(chk[qr[i].first] == 0) rv.push_back(qr[i].first);
	}
	lint rcv = cv;
	contract(m+1, e, rv, must_mst, maybe_mst);
	for(auto &i : must_mst) rcv += cost[i], disj.uni(st[i], ed[i], snapshot);
	solve(m+1, e, maybe_mst, rcv);
	disj.revert(snapshot);
	for(int i=s; i<=m; i++) chk[qr[i].first]++;
}

int main(){
	scanf("%d %d",&n,&m);
	vector<int> ve;
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&st[i],&ed[i],&cost[i]);
	}
	scanf("%d",&q);
	for(int i=0; i<q; i++){
		scanf("%d %d",&qr[i].first,&qr[i].second);
		qr[i].first--;
		chk[qr[i].first]++;
	}
	disj.init(n);
	for(int i=0; i<m; i++) if(!chk[i]) ve.push_back(i);
	solve(0, q-1, ve, 0);
}
