#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <numeric>
#include <functional>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <thread>
#include <tuple>
#include <limits>

using namespace std;

long long ptri[60][60];

int main() {
  int T;
  scanf("%d", &T);
  for (int i = 0; i < 60; i++) {
    ptri[i][0] = ptri[i][i] = 1;
    for (int j = 1; j < i; j++) {
      ptri[i][j] = ptri[i - 1][j - 1] + ptri[i - 1][j];
    }
  }
  while (T-- > 0) {
    long long key;
    scanf("%lld", &key);
    vector<int> fp;
    for (int d = 2; key > 0; d++) {
      fp.push_back(key%d);
      key /= d;
    }
    map<int, int> counter;
    int length = fp.size();
    for (int i = 0; i < fp.size(); i++) {
      counter[fp[i]]++;
    }
    vector<pair<int, int>> icnt(counter.begin(), counter.end());
    reverse(icnt.begin(), icnt.end());

    long long ans = -1;
    for (int i = 0; i < icnt.size(); i++) {
      if (icnt[i].first == 0) continue;
      icnt[i].second--;
      long long cur = 1;
      int sum = 1;
      for (auto p : icnt) {
        int ind, cnt;
        tie(ind, cnt) = p;
        int places = length - max(1,ind) + 1 - sum;
        cur *= ptri[places][cnt];
        sum += cnt;
      }
      ans += cur;
      icnt[i].second++;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
