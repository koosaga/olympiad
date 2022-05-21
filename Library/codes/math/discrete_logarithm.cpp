namespace discrete_log{
	lint product(lint x, lint y, lint MOD) {
		return x * y % MOD;
	}

	lint mod_pow(lint x, lint k, lint MOD) {
		if (!k) return 1;
		if (k&1) return product(x, mod_pow(x, k - 1, MOD), MOD);
		return mod_pow(product(x, x, MOD), k / 2, MOD);
	}

	lint totient(lint v) {
		lint tot = v;
		for (lint p = 2; p * p <= v; p++) if (v % p == 0) {
			tot = tot / p * (p - 1);
			while (v % p == 0) v /= p;
		}
		if (v > 1) tot = tot / v * (v - 1);
		return tot;
	}

	// https://judge.yosupo.jp/submission/32236
	/* Returns the smallest K >= 0 such that init * pow(x, K) === y modulo MOD.
	 * Returns -1 if no such K exists. Runs in O(sqrt(MOD)).
	 0 <= x, y < MOD, MOD not necessarily have to be prime
	 */
	lint solve(lint x, lint y, lint MOD, lint init = 1) {
		if (x == 0)
			return y == 1 ? 0 : y == 0 ? MOD > 1 : -1;

		lint prefix = 0;
		while (init != y && gcd(init, MOD) != gcd(product(init, x, MOD), MOD)) {
			init = product(init, x, MOD);
			prefix++;
		}

		if (init == y)
			return prefix;

		if (gcd(init, MOD) != gcd(y, MOD))
			return -1;

		MOD = MOD / gcd(init, MOD);

		x %= MOD;
		y %= MOD;
		init %= MOD;

		lint subgroup_order = totient(MOD);

		y = product(y, mod_pow(init, subgroup_order - 1, MOD), MOD);

		lint step_size = 0;
		while (step_size * step_size < subgroup_order)
			step_size++;

		unordered_map<lint, lint> table;

		lint baby_step = 1;
		for (lint i = 0; i < step_size; i++) {
			table[baby_step] = i;
			baby_step = product(baby_step, x, MOD);
		}

		lint giant_step = mod_pow(x, subgroup_order - step_size, MOD);
		for (lint i = 0; i < step_size; i++) {
			auto it = table.find(y);
			if (it != table.end())
				return prefix + i * step_size + it->second;
			y = product(y, giant_step, MOD);
		}

		return -1;
	}
}