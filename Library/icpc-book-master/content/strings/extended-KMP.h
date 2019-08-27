/**
 * Author: MIT NULL
 * Description: extended KMP
 * S[i] stores the maximum common prefix between s[i:] and t;
 * T[i] stores the maximum common prefix between t[i:] and t for i>0;
 */


int S[N], T[N];

void extKMP(const string&s, const string &t) {
  int m = t.size();
  T[0] = 0;
  int maT = 0;
  for (int i = 1; i < m; i++) {
    if (maT + T[maT] >= i) {
      T[i] = min(T[i - maT], maT + T[maT] - i);
    }else {
      T[i] = 0;
    }
    while (T[i] + i < m && t[T[i]] == t[T[i] + i])
      T[i]++;
    if (i + T[i] > maT + T[maT])
      maT = i;
  }
  int maS = 0;
  int n = s.size();
  for (int i = 0; i < n; i++) {
    if (maS + S[maS] >= i) {
      S[i] = min(T[i - maS], maS + S[maS] - i);
    }else {
      S[i] = 0;
    }
    while (S[i] < m && i + S[i] < n && t[S[i]] == s[S[i] + i])
      S[i]++;
    if (i + S[i] > maS + S[maS])
      maS = i;
  
  }
}

