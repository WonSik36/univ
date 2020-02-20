package edu.handong.csee.plt.ast.rbmrcfae;

import edu.handong.csee.plt.ast.AST;

public class Add implements RBMRCFAE {
	private AST lhs;
	private AST rhs;
	
	public Add(AST lhs, AST rhs) {
		this.lhs = lhs;
		this.rhs = rhs;
	}
	
	public AST getLhs() {
		return lhs;
	}

	public AST getRhs() {
		return rhs;
	}
	
	@Override
	public String getASTCode() {
		return "(add " + lhs.getASTCode() + " " + rhs.getASTCode() + ")";
	}

}
