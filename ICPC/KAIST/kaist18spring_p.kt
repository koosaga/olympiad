import kotlin.math.*
import java.util.*
import java.math.*

fun main(args : Array<String>){
	val br = java.io.BufferedReader(java.io.InputStreamReader(System.`in`), 32768)
	val bw = java.io.BufferedWriter(java.io.OutputStreamWriter(System.`out`))
	val (r, c, k) = br.readLine()!!.trim().split(" ").map{ it.toInt() }
	var arr = Array(r) { br.readLine()!!.trim().split(" ").map{ it.toInt() } }
	var h = Array(c) { 0 } 
	for (i in 0..(r-1)){
		for (j in 0..(c-1)){
			if(arr[i][j] != 0) h[j]++
		}
	}
	var x = Array(c){ it }
	x.sortBy{ h[it] }
	val l = mutableListOf<String>()
	for(v in 0..(c-1)){
		var i = x[v]
		for(j in 1..(h[i] / 2)){
			l.add("1 " + (i+1).toString() + " " + arr[r-2*j][i].toString() + " " + arr[r-2*j+1][i].toString() + "\n")
		}
		if(h[i] % 2 == 1){
			var cur = arr[r-h[i]][i]
			var nxt = cur + 1
			if(nxt == k + 1) nxt = 1
			l.add("1 " + (i+1).toString() + " $nxt $cur\n")
			l.add("1 " + (i+1).toString() + " $nxt $nxt\n")
			l.add("1 " + (i+1).toString() + " $nxt $nxt\n")
		}
	}
	bw.write(l.size.toString() + "\n")
	for(i in l) bw.write(i)
	bw.flush()
}
