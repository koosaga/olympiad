#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 2000000000
#define max(x, y) ((x) > (y) ? (x) : (y))
int n, i, ss, Case, m, tt[10], it1[10][10], it2[10][10], p[40], se[40];
char S[10], S1[10];

int calc(int x, int y, int z, int now) {
	int s = p[x] + p[y] + p[z];
	if ((se[x] == now) + (se[y] == now) + (se[z] == now) > 1)	return s;
	else	return -s;
}

int AlphaBeta(int h, int alpha, int beta, int now, int sum) {
	if (h > m * 2) {
		if (se[tt[now]] == now)	sum += p[tt[now]];
		else	sum -= p[tt[now]];
		if (se[tt[1 - now]] == 1 - now)	sum -= p[tt[1 - now]];
		else	sum += p[tt[1 - now]];
		return sum;
	}
	int val;
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j < 5 - i; j++) {
			if (it1[i][j * 2] && it1[i][j * 2 + 1] && !it2[i][j]) {
				it2[i][j] = h;
				val = -AlphaBeta(h + 1, -beta, -alpha, 1 - now, -sum - calc(it1[i][j * 2], it1[i][j * 2 + 1], it2[i][j], now));
				it2[i][j] = 0;
				if (val >= beta)	return beta;
				alpha = max(alpha, val);
				if (tt[now]) {
					it2[i][j] = tt[now];
					tt[now] = h;
					val = -AlphaBeta(h + 1, -beta, -alpha, 1 - now, -sum - calc(it1[i][j * 2], it1[i][j * 2 + 1], it2[i][j], now));
					tt[now] = it2[i][j];
					it2[i][j] = 0;
					if (val >= beta)	return beta;
					alpha = max(alpha, val);
				}
			}
		}
	if (tt[now])
	for (int i = 2; i <= 4; i++)
		for (int j = 1; j <= 5 - i; j++)
			if (it2[i - 1][j] && !it1[i][j * 2 - 1] && !it1[i][j * 2]) {
				int x = tt[now];
				it1[i][j * 2 - 1] = tt[now];
				it1[i][j * 2] = h;
				tt[now] = 0;
				val = -AlphaBeta(h + 1, -beta, -alpha, 1 - now, -sum - calc(it1[i][j * 2 - 1], it1[i][j * 2], it2[i - 1][j], now));
				it1[i][j * 2 - 1] = 0;
				it1[i][j * 2] = 0;
				tt[now] = x;
				if (val >= beta)	return beta;
				alpha = max(alpha, val);
				it1[i][j * 2 - 1] = h;
				it1[i][j * 2] = tt[now];
				tt[now] = 0;
				val = -AlphaBeta(h + 1, -beta, -alpha, 1 - now, -sum - calc(it1[i][j * 2 - 1], it1[i][j * 2], it2[i - 1][j], now));
				it1[i][j * 2 - 1] = 0;
				it1[i][j * 2] = 0;
				tt[now] = x;
				if (val >= beta)	return beta;
				alpha = max(alpha, val);
			}
	if (!tt[now]) {
		tt[now] = h;
		val = -AlphaBeta(h + 1, -beta, -alpha, 1 - now, -sum);
		tt[now] = 0;
		if (val >= beta)	return beta;
		alpha = max(alpha, val);
	}
	return alpha;
}

int main() {
	// freopen("data1.in", "r", stdin);
	while (true) {
		scanf("%s", S);
		if (S[0] == 'E')	return 0;
		scanf("%d", &m);
		ss = (S[0] == 'B');
		for (i = 1; i <= 2 * m; i++) {
			scanf("%s", S1);
			if (strlen(S1) == 2)	p[i] = S1[0] - '0';
			else	p[i] = 10 + S1[1] - '0';
			se[i] = (S1[strlen(S1) - 1] == 'B');
		}
		for (i = 1; i <= 8; i++)	it1[1][i] = i;
		tt[0] = 0;
		tt[1] = 0;
		int val = AlphaBeta(9, -INF, INF, se[1], 0);
		if (ss != se[1])	val = -val;
		printf("Case %d: ", ++Case);
		if (val > 0) {
			if (ss)	printf("Birgit wins %d\n", val);
			else	printf("Axel wins %d\n", val);
		}else if (val < 0) {
			if (ss)	printf("Birgit loses %d\n", -val);
			else	printf("Axel loses %d\n", -val);
		}else	printf("Axel and Birgit tie\n");
	}
}
