package edu.handong.csee.plt.ast.rbmrcfae;

public class Mult implements RBMRCFAE {
	private RBMRCFAE lhs;
	private RBMRCFAE rhs;
	
	public Mult(RBMRCFAE lhs, RBMRCFAE rhs) {
		this.lhs = lhs;
		this.rhs = rhs;
	}
	
	public RBMRCFAE getLhs() {
		return lhs;
	}

	public RBMRCFAE getRhs() {
		return rhs;
	}
	
	@Override
	public String getASTCode() {
		return "(mult " + lhs.getASTCode() + " " + rhs.getASTCode() + ")";
	}

}
