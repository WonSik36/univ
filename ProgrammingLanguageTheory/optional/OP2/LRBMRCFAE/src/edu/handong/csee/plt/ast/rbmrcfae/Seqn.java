package edu.handong.csee.plt.ast.rbmrcfae;

public class Seqn implements RBMRCFAE {
	private RBMRCFAE ex1;
	private RBMRCFAE ex2;
	
	public Seqn(RBMRCFAE ex1, RBMRCFAE ex2) {
		this.ex1 = ex1;
		this.ex2 = ex2;
	}
	
	public RBMRCFAE getExpr1() {
		return ex1;
	}
	
	public RBMRCFAE getExpr2() {
		return ex2;
	}
	
	@Override
	public String getASTCode() {
		return "(seqn "+ ex1.getASTCode()+" "+ ex2.getASTCode() +")";
	}

}
