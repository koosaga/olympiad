#include "roads.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
 
lint dp[MAXN];
int par[MAXN], pae[MAXN];
vector<pi> gph[MAXN];
vector<int> dfn;

struct jaryoguzo{
  multiset<lint> s, exc;
  int cur_thres;
  lint sumS;
  void init(int n){
    cur_thres = n;
  }
  void insert(lint x){
    sumS += x;
    s.insert(x);
    if(sz(s) > cur_thres){
      sumS -= *s.rbegin();
      exc.insert(*s.rbegin());
      s.erase(--s.end());
    }
  }
  void erase(lint x){
    if(exc.find(x) != exc.end()){
      exc.erase(exc.find(x));
    }
    else{
      sumS -= x;
      s.erase(s.find(x));
      if(sz(exc)){
        sumS += *exc.begin();
        s.insert(*exc.begin());
        exc.erase(exc.begin());
      }
    }
  }
  void shrink(){
    if(sz(s) == cur_thres){
      sumS -= *s.rbegin();
      exc.insert(*s.rbegin());
      s.erase(--s.end());
    }
    cur_thres--;
  }
  lint get_sum(){
    return sumS;
  }
  lint get_pos(){
    if(sz(s) == cur_thres) return *s.rbegin();
    return 0;
  }
}ds[MAXN];

void dfs(int x, int p = -1){
  dfn.push_back(x);
  for(auto &[w, y] : gph[x]){
    pae[y] = w;
    par[y] = x;
    gph[y].erase(find(all(gph[y]), pi(w, x)));
    dfs(y, x);
  }
}

std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W) {
    for(int i = 0; i < N - 1; i++){
      gph[U[i]].emplace_back(W[i], V[i]);
      gph[V[i]].emplace_back(W[i], U[i]);
  }
  dfs(0);
  vector<lint> ans(N);
  reverse(all(dfn));
  ans[0] = accumulate(all(W), 0ll);
 
  vector<vector<int>> cnd(N);
  for(int i = 0; i < N; i++) ds[i].init(sz(gph[i]));
  for(int i = 1; i < N; i++){
    dp[i] = -pae[i];
    ds[par[i]].insert(dp[i]);
  }
  for(auto &i : dfn){
    for(int j = 0; j <= sz(gph[i]) + 1 && j < N; j++) cnd[j].push_back(i);
  }
  for(int k = N - 2; k > 0; k--){
    ans[k] = ans[k + 1];
    for(auto &j : cnd[k]){
      if(sz(gph[j]) > k){
        lint val = ds[j].get_pos();
        ans[k] -= val;
        ds[j].shrink();
      }
    }
    for(auto &j : cnd[k]){
      if(j != 0){
        ans[k] -= ds[par[j]].get_sum();
        ds[par[j]].erase(dp[j]);
      }
      if(sz(gph[j]) == k - 1) dp[j] = -pae[j];
      else dp[j] = min(-ds[j].get_pos() - pae[j], 0ll);
      if(j != 0){
        ds[par[j]].insert(dp[j]);
        ans[k] += ds[par[j]].get_sum();
      }
    }
  }
  return ans;
}

