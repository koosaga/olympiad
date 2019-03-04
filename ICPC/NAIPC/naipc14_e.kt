import kotlin.math.*
import java.util.*

fun gcd(x : Int, y : Int) : Int{
	if(y == 0) return x
	return gcd(y, x%y) 
}

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	while(true){
		var n = readLine()!!.toInt()
		if(n == 0) break
		var arr = Array(n) { readLine()!!.toInt() } 
		var lst = Array(101) { it }
		var chk = Array(101) { false } 
		var ans = 0
		for (i in 0..(n-1)){
			for (j in 0..100){
				if(lst[j] == arr[i]){
					for(k in j downTo 1){
						lst[k] = lst[k-1]
					}
					lst[0] = arr[i]
					break
				}
			}
			var g = arr[i]
			for (j in 0..100){
				chk[g] = true
				if(lst[j] == 0) break
				g = gcd(g, lst[j])
			}
		}
		for (i in 1..100) if(chk[i]) ans++
		println(ans)
	}
}
