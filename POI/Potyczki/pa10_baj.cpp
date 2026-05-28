#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
int r = 0;

pair<int, int> INF = {0, 1000000010};

pi input() {
    int c;
    scanf("%d", &c);

    if (c == 0) {
        int a, b;
        scanf("%d%d", &a, &b);
        return {a, b};
    } else {
        vector<pi> vect;
        for (int i = 0; i < c; i++) {
            vect.push_back(input());
        }
        pi mem = INF;

        for (auto &g : vect) {
            mem.first = max(mem.first, g.first);
        }
        for (auto &g : vect) {
            if (g.second < mem.first)
                r++;
            else
                mem.second = min(mem.second, g.second);
        }
        return mem;
    }
}

int main() {
    input();
    printf("%d", r + 1);

    return 0;
}
