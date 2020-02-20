package edu.handong.csee.plt.ast.value;

public class NumV implements Value {
	String num = "0";
	
	public NumV(String num){
		this.num = num;
	}
	
	public String getStrNum() {
		return num;
	}
	
	@Override
	public String getASTCode() {
		return "(numV " + num +")";
	}
}
