import kotlin.math.*
import java.util.*
import java.math.*

val inf = 987654321

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	while(true){
		var n = nextInt()
		var m = nextInt()
		if(n == 0) break
		var arr = Array(n) { nextInt() } 
		var adj = Array(n) { Array(n) { inf } }
		for (i in 0..(n-1)) adj[i][i] = 0
		for (i in 1..m){
			var s = nextInt() - 1
			var e = nextInt() - 1
			adj[s][e] = (if (arr[s] == arr[e]) 0 else 1)
			adj[e][s] = (if (arr[s] == arr[e]) 0 else 1)
		}
		for (i in 0..(n-1)){
			for (j in 0..(n-1)){
				for (k in 0..(n-1)){
					adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
				}
			}
		}
		var ans = inf
		for (i in 0..(n-1)){
			var tmp = 0
			for (j in 0..(n-1)){
				tmp = max(tmp, adj[i][j])
			}
			ans = min(ans, tmp)
		}
		println(ans)
	}
}
