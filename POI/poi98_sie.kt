import java.util.*
import java.math.BigInteger
import kotlin.math.abs
import kotlin.math.min

fun main(args : Array<String>) = with(Scanner(System.`in`)) {
	var n = nextInt()
	var arr = Array(n+1) { Array(n+1) { 0 }}
	for (i in 1..n){
		for (j in 1..n){
			arr[i][j] = nextInt()
		}
	}
	for (i in 1..n){
		for (j in (i+1)..n){
			var brak = false
			for (k in 1..n){
				if(k != i && k != j && arr[i][k] + arr[k][j] == arr[i][j]){
					brak = true
				}
			}
			if(!brak) println(i.toString() + " " + j.toString())
		}
	}
}