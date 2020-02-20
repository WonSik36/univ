package edu.handong.csee.plt.ast.rbmrcfae;

import edu.handong.csee.plt.ast.AST;

public class Sub implements RBMRCFAE {
	AST lhs;
	AST rhs;
	
	public Sub(AST lhs, AST rhs) {
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
		return "(sub " + lhs.getASTCode() + " " + rhs.getASTCode() + ")";
	}
	
}
