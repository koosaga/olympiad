#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef vector<int> vi;
// END NO SAD

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int get(int x, int s) {
  // x as sum of s and s-1
  if(x%s == 0) return x/s;
  int cand = x/s + 1;
  if(cand * (s-1) <= x && cand * s >= x) return cand;
  return -1;
}

void rsolve() {
  int n;
  cin >> n;
  vector<int> v(n);
  for(int i = 0; i < n; i++) cin >> v[i];
  sort(all(v));
  map<int, int> dp;
  for(int i = 0; i < n;) {
    int j = i+1;
    while(j < n && v[i] == v[j]) j++;
    dp[j-i]++;
    i = j;
  }
  int ret = n;
  int smallest = dp.begin()->first;
  for(int s = smallest+1; s > 1; s--) {
    int cand = 0;
    for(auto out: dp) {
      int need = get(out.first, s);
      if(need == -1) {
        cand = n;
        break;
      }
      cand += need * out.second;
      if(cand >= ret) break;
    }
    ret = min(ret, cand);
  }
  cout << ret << "\n";
}

void solve() {
  int t;
  cin >> t;
  while(t--) rsolve();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  solve();
}
