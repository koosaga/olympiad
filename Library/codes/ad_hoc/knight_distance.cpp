// Given a board of size nx * ny, find the shortest knight distance from (kx, ky) to (cx, cy)
// Need nx >= 8, ny >= 8, 0 <= kx, cx < nx and vice versa
// Source: Official package of BAPC 2017

int knightDistance(int nx, int ny, int kx, int ky, int cx, int cy) {
	int x = abs(cx - kx), y = abs(cy - ky);
	if (x < y)
		swap(x, y), swap(nx, ny), swap(cx, cy), swap(kx, ky);
	if (x == 1 && y == 0)
		return 3;
	if (x == 2 && y == 2)
		return 4;
	if (x == 1 && y == 1 && (((cx == 0 || cx == nx - 1) && (cy == 0 || cy == ny - 1)) || ((kx == 0 || kx == nx - 1) && (ky == 0 || ky == ny - 1))))
		return 4;
	int steps = max((x + y + 2) / 3, (x + 1) / 2);
	return steps + ((x + y + steps) % 2);
}