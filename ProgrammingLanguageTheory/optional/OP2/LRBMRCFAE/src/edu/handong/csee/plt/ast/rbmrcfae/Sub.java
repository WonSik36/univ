package edu.handong.csee.plt.ast.rbmrcfae;

public class Sub implements RBMRCFAE {
	RBMRCFAE lhs;
	RBMRCFAE rhs;
	
	public Sub(RBMRCFAE lhs, RBMRCFAE rhs) {
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
		return "(sub " + lhs.getASTCode() + " " + rhs.getASTCode() + ")";
	}
	
}
