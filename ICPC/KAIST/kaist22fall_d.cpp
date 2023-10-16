#include <bits/stdc++.h>
using namespace std;
using lint = long long;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    lint n, a, l, r;
    cin >> n >> a >> l >> r;
    for (int i = 1; i <= n; i++)
    {
        if (a % i == 0 && l <= a / i && a / i <= r && (__int128) l * n <= a)
        {
                cout << "YES\n";
                for (int j = 0; j < n; j++)
                {
                    if (j < i)
                        cout << a / i << " ";
                    else
                        cout << l << " ";
                }
                return 0;
        }
    }
    cout << "NO\n";
}