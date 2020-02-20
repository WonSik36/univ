package edu.handong.csee.plt.ast.rbmrcfae;

public class Add implements RBMRCFAE {
	private RBMRCFAE lhs;
	private RBMRCFAE rhs;
	
	public Add(RBMRCFAE lhs, RBMRCFAE rhs) {
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
		return "(add " + lhs.getASTCode() + " " + rhs.getASTCode() + ")";
	}

}
