/**
 *    author:  tourist
 *    created: 02.03.2024 00:00:10
**/
#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int a, p;
    string s, e;
    cin >> a >> p >> s >> e;
    vector<string> dir = {s};
    vector<string> rev = {e};
    if (s == string(s.size(), s[0])) {
      char other = 'A' ^ 'P' ^ s[0];
      s.insert(s.end() - 1, other);
      s.push_back(other);
      dir.push_back(s);
    }
    if (e == string(e.size(), e[0])) {
      char other = 'A' ^ 'P' ^ e[0];
      e += string(other == 'A' ? a : p, other);
      rev.push_back(e);
    }
    while (true) {
      s = dir.back();
      bool found = false;
      bool met = false;
      for (int i = 0; i < int(s.size()); i++) {
        if (met && s.substr(i, a) == string(a, 'A')) {
          s.erase(s.begin() + i, s.begin() + i + a);
          dir.push_back(s);
          found = true;
          break;
        }
        if (s[i] == 'A') {
          met = true;
        }
      }
      if (found) {
        continue;
      }
      met = false;
      for (int i = 0; i < int(s.size()); i++) {
        if (met && s.substr(i, p) == string(p, 'P')) {
          s.erase(s.begin() + i, s.begin() + i + p);
          dir.push_back(s);
          found = true;
          break;
        }
        if (s[i] == 'P') {
          met = true;
        }
      }
      if (found) {
        continue;
      }
      for (int i = int(s.size()) - 2; i >= 0; i--) {
        if (s[i] == 'A' && s[i + 1] == 'P') {
          s.insert(s.begin() + i + 1, 'P');
          s.insert(s.begin() + i, 'P');
          dir.push_back(s);
          found = true;
          break;
        }
      }
      if (found) {
        continue;
      }
      int np = 0, na = 0;
      for (char c : s) {
        if (c == 'P') {
          np += 1;
        }
        if (c == 'A') {
          na += 1;
        }
      }
      assert(np > 0 && na > 0);
      auto PPtoAA = [&](string pref, string suf) {
        for (int i = 1; i <= p; i++) {
          dir.push_back(pref + string(i, 'P') + "A" + string(i, 'P') + "A" + suf);
        }
        dir.push_back(pref + string(p, 'P') + "A" + "A" + suf);
        dir.push_back(pref + "A" + "A" + suf);
      };
      auto AAtoPP = [&](string pref, string suf) {
        for (int i = 1; i <= a; i++) {
          dir.push_back(pref + string(i, 'A') + "P" + string(i, 'A') + "P" + suf);
        }
        dir.push_back(pref + string(a, 'A') + "P" + "P" + suf);
        dir.push_back(pref + "P" + "P" + suf);
      };
      auto RemovePPPP = [&]() {
        PPtoAA("", s.substr(2));
        s = dir.back();
        PPtoAA(s.substr(0, 3), s.substr(5));
        s = dir.back();
        for (int it = 0; it < a - 2; it++) {
          s.insert(s.begin() + (3 + it), 'A');
          s.insert(s.begin() + (2 + it), 'A');
          dir.push_back(s);
        }
        s.erase(s.begin(), s.begin() + a);
        dir.push_back(s);
        s.erase(s.begin() + 1, s.begin() + a + 1);
        dir.push_back(s);
      };
      auto RemoveAAAA = [&]() {
        AAtoPP(s.substr(0, s.size() - 2), "");
        s = dir.back();
        AAtoPP(s.substr(0, s.size() - 5), s.substr(s.size() - 3));
        s = dir.back();
        for (int it = 0; it < p - 2; it++) {
          s.insert(s.end() - (3 + it), 'P');
          s.insert(s.end() - (2 + it), 'P');
          dir.push_back(s);
        }
        s.erase(s.end() - p, s.end());
        dir.push_back(s);
        s.erase(s.end() - p - 1, s.end() - 1);
        dir.push_back(s);
      };
      if (np >= 5) {
        RemovePPPP();
        continue;
      }
      if (na >= 5) {
        RemoveAAAA();
        continue;
      }
      if (np % 2 == 0 && p % 2 == 1) {
        int rep = 1;
        for (int i = 0; i < rep * p; i++) {
          s.insert(s.begin() + np + 1, 'P');
          s.insert(s.begin() + np, 'P');
          dir.push_back(s);
          np += 1;
        }
        for (int i = 0; i < rep; i++) {
          s.erase(s.begin() + np + 1, s.begin() + np + 1 + p);
        }
        dir.push_back(s);
        while (np >= 5) {
          RemovePPPP();
          s = dir.back();
          np -= 4;
        }
        continue;
      }
      if (na % 2 == 0 && a % 2 == 1) {
        int rep = 1;
        for (int i = 0; i < rep * a; i++) {
          s.insert(s.begin() + np + i, 'A');
          s.insert(s.begin() + np - 1 + i, 'A');
          dir.push_back(s);
          na += 1;
        }
        for (int i = 0; i < rep; i++) {
          s.erase(s.begin() + np - 1, s.begin() + np - 1 + a);
        }
        dir.push_back(s);
        while (na >= 5) {
          RemoveAAAA();
          s = dir.back();
          na -= 4;
        }
        continue;
      }
      if (np >= 3 && p % 4 != 0) {
        int rep = (p % 4 == 2 ? 1 : 2);
        for (int i = 0; i < rep * p; i++) {
          s.insert(s.begin() + np + 1, 'P');
          s.insert(s.begin() + np, 'P');
          dir.push_back(s);
          np += 1;
        }
        for (int i = 0; i < rep; i++) {
          s.erase(s.begin() + np + 1, s.begin() + np + 1 + p);
          dir.push_back(s);
        }
        while (np >= 5) {
          RemovePPPP();
          s = dir.back();
          np -= 4;
        }
        continue;
      }
      if (na >= 3 && a % 4 != 0) {
        int rep = (a % 4 == 2 ? 1 : 2);
        for (int i = 0; i < rep * a; i++) {
          s.insert(s.begin() + np + i, 'A');
          s.insert(s.begin() + np - 1 + i, 'A');
          dir.push_back(s);
          na += 1;
        }
        for (int i = 0; i < rep; i++) {
          s.erase(s.begin() + np - 1, s.begin() + np - 1 + a);
          dir.push_back(s);
        }
        while (na >= 5) {
          RemoveAAAA();
          s = dir.back();
          na -= 4;
        }
        continue;
      }
      if (np >= 3 && a % 4 != 0) {
        PPtoAA(s.substr(0, np - 2), s.substr(np));
        continue;
      }
      if (na >= 3 && p % 4 != 0) {
        AAtoPP(s.substr(0, np), s.substr(np + 2));
        continue;
      }
      if (np >= 3 && p % 4 == 0 && a % 4 == 0) {
        PPtoAA(s.substr(0, np - 2), s.substr(np));
        continue;
      }
      break;
    }

    while (true) {
      s = rev.back();
      bool found = false;
      for (int i = int(s.size()) - 3; i >= 0; i--) {
        if (s.substr(i, 3) == "PAP" || s.substr(i, 3) == "APA") {
          s.erase(s.begin() + i + 2);
          s.erase(s.begin() + i);
          rev.push_back(s);
          found = true;
          break;
        }
      }
      if (found) {
        continue;
      }
      for (int i = int(s.size()) - 2; i >= 0; i--) {
        if (s[i] == 'A' && s[i + 1] == 'P') {
          s = s.substr(0, i) + string(p, 'P') + s.substr(i);
          rev.push_back(s);
          found = true;
          break;
        }
      }
      if (found) {
        continue;
      }
      int np = 0, na = 0;
      for (char c : s) {
        if (c == 'P') {
          np += 1;
        }
        if (c == 'A') {
          na += 1;
        }
      }
      if (np == 0) {
        s = string(p, 'P') + s;
        rev.push_back(s);
        continue;
      }
      if (na == 0) {
        s = s + string(a, 'A');
        rev.push_back(s);
        continue;
      }
      assert(np > 0 && na > 0);
      auto PPtoAA = [&](string pref, string suf) {
        rev.push_back(pref + string(a, 'A') + "P" + "P" + suf);
        for (int i = a; i >= 1; i--) {
          rev.push_back(pref + string(i, 'A') + "P" + string(i, 'A') + "P" + suf);
        }
        rev.push_back(pref + "A" + "A" + suf);
      };
      auto AAtoPP = [&](string pref, string suf) {
        rev.push_back(pref + string(p, 'P') + "A" + "A" + suf);
        for (int i = p; i >= 1; i--) {
          rev.push_back(pref + string(i, 'P') + "A" + string(i, 'P') + "A" + suf);
        }
        rev.push_back(pref + "P" + "P" + suf);
      };
      auto RemovePPPP = [&]() {
        PPtoAA("", s.substr(2));
        s = rev.back();
        PPtoAA(s.substr(0, 3), s.substr(5));
        s = rev.back();
        s.erase(s.begin() + 3);
        s.erase(s.begin());
        rev.push_back(s);
        s.erase(s.begin() + 2);
        s.erase(s.begin());
        rev.push_back(s);
      };
      auto RemoveAAAA = [&]() {
        AAtoPP(s.substr(0, s.size() - 2), "");
        s = rev.back();
        AAtoPP(s.substr(0, s.size() - 5), s.substr(s.size() - 3));
        s = rev.back();
        s.erase(s.end() - 4);
        s.erase(s.end() - 1);
        rev.push_back(s);
        s.erase(s.end() - 3);
        s.erase(s.end() - 1);
        rev.push_back(s);
      };
      if (np >= 5) {
        RemovePPPP();
        continue;
      }
      if (na >= 5) {
        RemoveAAAA();
        continue;
      }
      if (np % 2 == 0 && p % 2 == 1) {
        s = string(p, 'P') + s;
        rev.push_back(s);
        continue;
      }
      if (na % 2 == 0 && a % 2 == 1) {
        s = s + string(a, 'A');
        rev.push_back(s);
        continue;
      }
      if (np >= 3 && p % 4 != 0) {
        int rep = (p % 4 == 2 ? 1 : 2);
        for (int i = 0; i < rep; i++) {
          s = string(p, 'P') + s;
          rev.push_back(s);
        }
        continue;
      }
      if (na >= 3 && a % 4 != 0) {
        int rep = (a % 4 == 2 ? 1 : 2);
        for (int i = 0; i < rep; i++) {
          s = s + string(a, 'A');
          rev.push_back(s);
        }
        continue;
      }
      if (np >= 3 && a % 4 != 0) {
        PPtoAA(s.substr(0, np - 2), s.substr(np));
        continue;
      }
      if (na >= 3 && p % 4 != 0) {
        AAtoPP(s.substr(0, np), s.substr(np + 2));
        continue;
      }
      if (np >= 3 && p % 4 == 0 && a % 4 == 0) {
        PPtoAA(s.substr(0, np - 2), s.substr(np));
        continue;
      }
      break;
    }
    if (dir.back() != rev.back()) {
      cout << -1 << '\n';
      continue;
    }
    vector<string> seq = dir;
    reverse(rev.begin(), rev.end());
    seq.insert(seq.end(), rev.begin() + 1, rev.end());
    assert(seq.size() <= 35001);
    cout << seq.size() - 1 << '\n';
    for (int it = 0; it < int(seq.size()) - 1; it++) {
      s = seq[it];
      e = seq[it + 1];
      bool found = false;
      if (e.size() == s.size() + 2) {
        for (int i = 0; i < int(s.size()); i++) {
          if (s[i] != e[i]) {
            cout << "+" << s[i] << " " << i + 1 << '\n';
            found = true;
            break;
          }
        }
      }
      if (!found && e.size() + a == s.size()) {
        for (int i = 0; i < int(s.size()); i++) {
          if (s.substr(i, a) == string(a, 'A') && s.substr(0, i) + s.substr(i + a) == e) {
            cout << "-A " << i + 1 << '\n';
            found = true;
            break;
          }
        }
      }
      if (!found && e.size() + p == s.size()) {
        for (int i = 0; i < int(s.size()); i++) {
          if (s.substr(i, p) == string(p, 'P') && s.substr(0, i) + s.substr(i + p) == e) {
            cout << "-P " << i + 1 << '\n';
            found = true;
            break;
          }
        }
      }
      assert(found);
    }
  }
  return 0;
}
