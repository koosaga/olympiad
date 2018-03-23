import java.util.*
import java.math.BigInteger
import kotlin.math.abs
import kotlin.math.min

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	var n = nextInt()
	var v = mutableListOf<Pair<Int, Int>>();
	var dp = Array(n) { 0 }
	for (i in 1..n){
		var l = nextInt()
		var r = nextInt()
		v.add(Pair(l, r))
	}
	v.sortBy{ it.second }
	for (i in 0..(n-1)){
		for (j in 0..(i-1)){
			if(v[j].second <= v[i].first) dp[i] = Math.max(dp[i], dp[j])
		}
		dp[i] += v[i].second - v[i].first;
		if(i > 0) dp[i] = Math.max(dp[i], dp[i-1])
	}
	println(dp[n-1])

}

