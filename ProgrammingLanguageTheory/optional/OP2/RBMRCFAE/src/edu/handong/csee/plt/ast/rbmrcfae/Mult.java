package edu.handong.csee.plt.ast.rbmrcfae;

import edu.handong.csee.plt.ast.AST;

public class Mult implements RBMRCFAE {

	private AST lhs;
	private AST rhs;
	
	public Mult(AST lhs, AST rhs) {
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
		return "(mult " + lhs.getASTCode() + " " + rhs.getASTCode() + ")";
	}

}
