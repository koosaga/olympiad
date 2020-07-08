maxflow mf;
lint lsum;
void clear(){
	lsum = 0;
	mf.clear();
}
void add_edge(int s, int e, int l, int r){
	lsum += l;
	mf.add_edge(s + 2, e + 2, r - l);
	mf.add_edge(0, e + 2, l);
	mf.add_edge(s + 2, 1, l);
}
bool solve(int s, int e){
	mf.add_edge(e+2, s+2, 1e9); // to reduce as maxflow with lower bounds, in circulation problem skip this line
	return lsum == mf.match(0, 1);
	// to get maximum LR flow, run maxflow from s+2 to e+2 again
}