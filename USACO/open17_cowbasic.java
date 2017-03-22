import java.util.Scanner;
import java.util.Stack;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
	static int mod = 1000000007;
	static class Matrix{
		int n;
		int[][] col;
		Matrix(int n){
			this.n = n;
			col = new int[n][n];
			for(int i=0; i<n; i++){
				col[i][i] = 1;
			}
		}
		void set_multiply(Matrix b){
			int nxtn = Math.max(n, b.n);
			long[][] tcol = new long[nxtn][nxtn];
			for(int i=0; i<nxtn; i++){
				for(int j=0; j<nxtn; j++){
					for(int k=0; k<nxtn; k++){
						int a = 0;
						if(i < n && k < n){
							a = col[i][k];
						}
						else a = (i == k ? 1 : 0);
						int c = 0;
						if(k < b.n && j < b.n){
							c = b.col[k][j];
						}
						else{
							c = (j == k ? 1 : 0);
						}
						tcol[i][j] += (long)a*(long)c;
						tcol[i][j] %= mod;
					}
				}
			}
			n = nxtn;
			col = new int[n][n];
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					col[i][j] = (int)tcol[i][j];
				}
			}
		}
		void debug(){
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					System.out.print(col[i][j] + " ");
				}
				System.out.println("");
			}
		}
		void power(int x){
			Matrix ret = new Matrix(n);
			while(x > 0){
				if(x%2 == 1) ret.set_multiply(this);
				this.set_multiply(this);
				x /= 2;
			}
			for(int i=0; i<n; i++){
				for(int j=0; j<n; j++){
					col[i][j] = ret.col[i][j];
				}
			}
		}
	}
	static boolean is_literal(String s){
		for(int i=0; i<s.length(); i++){
			if(s.charAt(i) > '9' || s.charAt(i) < '0') return false;
		}
		return true;
	}
	static boolean is_variable(String s){
		for(int i=0; i<s.length(); i++){
			if(s.charAt(i) > 'z' || s.charAt(i) < 'a') return false;
		}
		return true;
	}
	public static void main(String[] args){
		Scanner in;
    try {
        in = new Scanner(new File("cowbasic.in"));
    } catch (FileNotFoundException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        return;
    }
    
    
    PrintWriter writer;
    try {
		writer = new PrintWriter("cowbasic.out");
    } catch (FileNotFoundException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        return;
    }
	/*	Scanner in = new Scanner(System.in);
		PrintWriter writer = new PrintWriter(System.out);
    */
		HashMap<String, Integer> mp = new HashMap<String, Integer>();
		Stack<Integer> stk = new Stack<Integer>();
		Stack<Matrix> stk2 = new Stack<Matrix>();
		Matrix m = new Matrix(1);
		int sz = 0;
		while(true){
			String t = in.nextLine();
			String[] ww = t.split(" ");
			ArrayList<String> w = new ArrayList<String>();
			for(int i=0; i<ww.length; i++){
				if(ww[i].length() > 0){
					w.add(ww[i]);
				}
			}
			if(is_literal(w.get(0))){
				Integer i = Integer.parseInt(w.get(0));
				stk.push(i);
				stk2.push(m);
				m = new Matrix(sz + 1);				
			}
			else if(w.get(0).equals("}")){
				int l = stk.pop();
				m.power(l);
				m.set_multiply(stk2.pop());
			}
			else if(w.get(0).equals("RETURN")){
				int ans = mp.get(w.get(1));
				writer.println(m.col[ans][0]);
				writer.close();
				in.close();
				return;
			}
			else{
				int nxt = 0;
				if(mp.containsKey(w.get(0))){
					nxt = mp.get(w.get(0));
				}
				else{
					sz++;
					mp.put(w.get(0), sz);
					nxt = sz;
				}
				Matrix mat = new Matrix(sz + 1);
				mat.col[nxt][nxt] = 0;
				for(int i=1; i<w.size(); i++){
					if(is_literal(w.get(i))){
						mat.col[nxt][0] += Integer.parseInt(w.get(i));
					}
					else if(is_variable(w.get(i))){
						int l = mp.get(w.get(i));
						mat.col[nxt][l]++;
					}
				}
				mat.set_multiply(m);
				m = mat;
			}
		}
	}
}
