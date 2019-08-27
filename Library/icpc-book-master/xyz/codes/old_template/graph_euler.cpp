/////////////////////////////
//// Graph Theory
// Euler path
///////////////////////////
multiset<int> e[maxn];

void eular(int cur) {
  while (!e[cur].empty()) {
    int x=*(e[cur].begin());
    e[cur].erase(e[cur].find(x));
    e[x].erase(e[x].find(cur));
    eular(x);
    ans.push_back(x);
  }
}
 
ans.clear();
eular(s);
ans.push_back(s);