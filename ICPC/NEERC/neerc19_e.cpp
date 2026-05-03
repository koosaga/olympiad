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

int r, c;
int g[105][105];
void solve() {
  cin >> c >> r;
  for(int i = 0; i < r; i++) for(int j = 0; j < c; j++) cin >> g[i][j];
  vector<int> cancel;
  for(int i = 0; i < r; i++) cancel.push_back(i);
  for(int j = 0; j < c-1; j++) {
    vector<pii> choices;
    for(int i = 0; i < r; i++) {
      choices.push_back({g[i][j] - g[i][c-1], i});
    }
    sort(all(choices));
    reverse(all(choices));
    int amt = 0;
    set<int> cand;
    for(int i = 0; i < r; i++) cand.insert(i);
    for(pii out: choices) {
      if(amt + out.first >= 0) {
        amt += out.first;
        cand.erase(out.second);
      }
    }
    if(sz(cand) < sz(cancel)) {
      cancel.clear();
      for(int out: cand) cancel.push_back(out);
    }
  }
  cout << sz(cancel) << "\n";
  for(int i = 0; i < sz(cancel); i++) {
    if(i) cout << " "; cout << cancel[i]+1;
  } cout << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
  solve();
}
