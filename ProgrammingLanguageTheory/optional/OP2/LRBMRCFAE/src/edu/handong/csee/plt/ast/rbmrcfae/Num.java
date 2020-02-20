package edu.handong.csee.plt.ast.rbmrcfae;

public class Num implements RBMRCFAE {
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
