// number of (x, y) : (0 <= x < n && 0 < y <= k/d x + b/d)
// argument should be positive
lint count_solve(lint n, lint k, lint b, lint d) {
	if (k == 0) {
		return (b / d) * n;
	}
	if (k >= d || b >= d) {
		return ((k / d) * (n - 1) + 2 * (b / d)) * n / 2 + count_solve(n, k % d, b % d, d);
	}
	return count_solve((k * n + b) / d, d, (k * n + b) % d, k);
}
