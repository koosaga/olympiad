///////////////////////////////////
//// Costflow – xhr
//zkw min-cost max-flow 
//assuming sink has largest label 
//sometimes works better than spfa flow
///////////////////////////////////
#define maxn 510
#define INF 1000000000
struct atype {
  int id, wg, cost, anti;
  atype() {}
  atype(int id, int wg, int cost, int anti): id(id), wg(wg), cost(cost), anti(anti) {}
};
vector<atype> e[maxn];
void add(int w, int x, int y, int z) {
  e[w].push_back(atype(x,y,z,e[x].size()));
  e[x].push_back(atype(w,0,-z,e[w].size()-1));
}
int source, sink, flow, augc;
int h[maxn], vis[maxn];
int aug(int m) {
  if (m==sink) {
    flow+=augc*h[source];
    return 1;
  }
  int augc2=augc; vis[m]=1;
  rept(it,e[m])
    if (it->wg && !vis[it->id] && h[m]==h[it->id]+it->cost) {
      augc=min(augc,it->wg);
      if (aug(it->id)) {
        it->wg-=augc; e[it->id][it->anti].wg+=augc;
        return 1;
      }
      augc=augc2;
    }
  return 0;
}
int relabel() {
  int minh=INF;
  rep(i,1,sink)
    if (vis[i])
      rept(it,e[i])
        if (it->wg && !vis[it->id])
          minh=min(minh,h[it->id]+it->cost-h[i]);
  if (minh==INF) return 0;
  rep(i,1,sink) if (vis[i]) h[i]+=minh;
  return 1;
}
void costflow() {
  flow=0;
  do {
    do {
      augc=INF; memset(vis,0,sizeof vis);
    } while (aug(source));
  } while (relabel());
} 
