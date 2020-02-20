package edu.handong.csee.plt.ast.rcfae;

public class Num implements RCFAE {
	String num;
	
	public Num(String num){
		this.num = num;
	}
	
	public String getStrNum() {
		return num;
	}
	
	public String getASTCode() {
		return "(num " + num +")";
	}
}
