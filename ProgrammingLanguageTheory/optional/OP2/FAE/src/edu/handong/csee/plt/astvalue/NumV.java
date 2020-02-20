package edu.handong.csee.plt.astvalue;

public class NumV extends ASTValue {
	String num = "0";
	
	public NumV(String num){
		this.num = num;
	}
	
	public String getStrNum() {
		return num;
	}
	
	@Override
	public String getASTValueCode() {
		return "(numV " + num +")";
	}
}
