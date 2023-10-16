#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353;
int arr[100010];

int main()
{
    int n, m, k, i, j, ans, flag;
    arr[0] = 0;
    scanf("%d %d %d", &m, &n, &k);
    for (i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (i = 0; i <= n - 1; i++)
        arr[i] = arr[i + 1] - arr[i] - 1;
    ans = 0;
    for (i = 0; i < k; i++)
    {
        flag = 1;
        for (j = n - i - 1; j >= 0; j -= k)
        {
            if (flag == 1)
                ans = ans ^ arr[j];
            flag = -flag;
        }
    }
    if (ans == 0)
        printf("Nova");
    else
        printf("Twinkle");
}