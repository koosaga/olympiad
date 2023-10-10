import kotlin.math.*
import java.util.*
import java.math.*

var str = arrayOf("New Customer\n", "Promising\n", "About to Sleep\n", "Hibernating\n", "Lost\n", "Potential Loyalist\n", "Need Attention\n", "About to Leave\n", "Champion\n", "Loyal Customer\n", "Can't Lose Them\n")
var arrMp = arrayOf( 
	intArrayOf(0, 1, 2, 4, 4),
	intArrayOf(5, 5, 2, 3, 4),
	intArrayOf(5, 5, 6, 7, 7),
	intArrayOf(9, 9, 9, 7, 7),
	intArrayOf(8, 9, 9, 7, 10))

fun main(args : Array<String>){
	val br = java.io.BufferedReader(java.io.InputStreamReader(System.`in`), 32768)
  	val bw = java.io.BufferedWriter(java.io.OutputStreamWriter(System.`out`))
	val arrR = br.readLine()!!.trim().split(" ").map{ it.toInt() } 
	val arrF = br.readLine()!!.trim().split(" ").map{ it.toInt() } 
	val q = br.readLine()!!.trim().toInt()
	var freq = TreeMap<String, Int>();
	var las = TreeMap<String, Int>();
	for(i in 1..q){
		var (x, y) = br.readLine()!!.trim().split(" ")
		if(x == "1"){
			las.put(y, i)
			freq.put(y, (freq.get(y) ?: 0) + 1) 
		}
		else{
			if(!freq.contains(y)){
				bw.write("None\n")
				continue
			}
			var f = freq.get(y)!!
			var r = i - las.get(y)!!
			bw.write(str[arrMp[arrF.filter{ it < f }.size][arrR.filter{ it < r }.size]])
		}
	}
	bw.flush()
	bw.close()
}


