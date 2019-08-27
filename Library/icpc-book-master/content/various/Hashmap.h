/**
 * Author: Andrew He
 * Description: Faster/better hash maps, taken from CF
 */
#pragma once

#include <ext/pb_ds/assoc_container.hpp> /** keep-include */
using namespace __gnu_pbds;
gp_hash_table<int, int> table;

struct custom_hash {
	size_t operator()(uint64_t x) const {
		x += 48;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
};
gp_hash_table<int, int, custom_hash> safe_table;
