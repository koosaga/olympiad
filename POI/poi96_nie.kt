import kotlin.math.*
import java.util.*
import java.math.*
val inf = 987654321

fun main(args : Array<String>){
	val n = readLine()!!.toInt()
	val arr = Array(n) { readLine()!!.toInt() }
	val dp = Array(n + 1) { Array(64){ -inf } }
	val cnt = Array(n + 1) { Array(64) { BigInteger.ZERO } }
	fun dist(x : Int, y : Int) : Int { 
		return abs(x - y)
	}
	dp[0][0] = 0
	cnt[0][0] = BigInteger.ONE
	for (i in 0..(n-1)){
		for (j in 0..63){
			for (k in 0..7){
				if(arr[i] != 0 && ((k shr (arr[i] - 1)) and 1) == 1){
					continue
				}
				val nxt = ((j shl 3) or k) and 63
				var ok = true
				var pcnt = 0
				for (l in 0..2){
					if(((k shr l) and 1) == 0){
						continue
					}
					pcnt++
					if(dist(l, 0) == 2 && (j and 1) > 0) ok = false
					if(dist(l, 1) == 2 && (j and 2) > 0) ok = false
					if(dist(l, 2) == 2 && (j and 4) > 0) ok = false
					if(dist(l, 0) == 1 && (j and 8) > 0) ok = false
					if(dist(l, 1) == 1 && (j and 16) > 0) ok = false
					if(dist(l, 2) == 1 && (j and 32) > 0) ok = false
				}
				if(ok){
					if(dp[i+1][nxt] < dp[i][j] + pcnt){
						dp[i+1][nxt] = dp[i][j] + pcnt
						cnt[i+1][nxt] = BigInteger.ZERO
					}
					if(dp[i+1][nxt] == dp[i][j] + pcnt){
						cnt[i+1][nxt] = cnt[i+1][nxt].add(cnt[i][j])
					}
				}
			}
		}
	}
	var ans = 0
	var dcnt = BigInteger.ZERO
	for (j in 0..63){
		if(ans < dp[n][j]){
			ans = dp[n][j]
			dcnt = BigInteger.ZERO
		}
		if(ans == dp[n][j]){
			dcnt = dcnt.add(cnt[n][j])
		}
	}
	println(ans.toString() + " " + dcnt.toString())
}
