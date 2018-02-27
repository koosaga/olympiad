#include<bits/stdc++.h>
using namespace std;
int N, a, b;
double dp1[3030][3030];

double solve1(int x, int y){
	for(int i=N; i>=0; i--){
		for(int j=N; j>=0; j--){
			if(i + j >= N) continue;
			int x = i, y = j;
			double res = 2.0;
			if(a - i > 0) res += dp1[i + 1][j] * 2 * (a - i);
			if(b - j > 0) res += dp1[i][j + 1] * (b - j);
			res /= (2.0 * (a - x) + b - y + 2);
			dp1[i][j] = res;
		}
	}
	return dp1[0][0];
}
double solve2(int x, int y)
{
	for(int i=0; i<3030; i++) fill(dp1[i], dp1[i] + 3030, 0);
	for(int i=N; i>=0; i--){
		for(int j=N; j>=0; j--){
			if(i + j >= N) continue;
			int x = i, y = j;
			double res = 1.0;
			if(a - i > 0) res += dp1[i + 1][j] * 2 * (a - i);
			if(b - j > 0) res += dp1[i][j + 1] * (b - j);
			res /= (2.0 * (a - x) + b - y + 1);
			dp1[i][j] = res;
		}
	}
	return dp1[0][0];
}
int main()
{
	freopen("bonus.in", "r", stdin);
	freopen("bonus.out", "w", stdout);
	scanf("%d%d%d", &N, &a, &b);
	if(a+b<N)
	{
		puts("1.0");
		puts("1.0");
		return 0;
	}

	printf("%.16f\n", solve1(0, 0));
	printf("%.16f\n", solve2(0, 0));
	return 0;
}
