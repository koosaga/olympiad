#include <bits/stdc++.h>
#include "perm.h"
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const lint mx = 2e18;

lint cnt(vector<int> v){
  vector<lint> dp(sz(v));
  lint sum = 1;
  for(int i = 0; i < sz(v); i++){
    dp[i] = 1;
    for(int j = 0; j < i; j++){
      if(v[j] < v[i]) dp[i] += dp[j];
      dp[i] = min(dp[i], mx);
    }
    sum += dp[i];
    sum = min(sum, mx);
  }
  return sum;
}

vector<int> construct_permutation(lint k){
  if(k == 1) return {};
  if(k == 2) return {0};
  if(k == 3) return {1, 0};
  auto ans = construct_permutation(k / 4);
  int n = sz(ans);
  if(k % 4 == 0){
    ans.push_back(n);
    ans.push_back(n + 1);
    return ans;
  }
  if(k % 4 == 1){
    ans.push_back(n + 0);
    ans.push_back(n + 1);
    ans.push_back(-1);
    for(auto &x : ans) x++;
    return ans;
  }
  if(k % 4 == 2){
    ans.push_back(n + 0);
    ans.push_back(-1);
    ans.push_back(n + 1);
    for(auto &x : ans) x++;
    return ans;
  }
  auto b = ans;
  ans.push_back(n + 0);
  ans.push_back(n + 1);
  for(int i = 0; i < sz(ans); i++) if(ans[i] > 1) ans[i]++;
  ans.push_back(2);
  if(cnt(ans) == k) return ans;
  for(auto &x : b) x += 2;
  b.push_back(n + 2);
  b.push_back(1);
  b.push_back(n + 3);
  b.push_back(0);
  return b;
}
