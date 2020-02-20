package edu.handong.csee.plt.ast;

public class With extends AST {
	String id;
	AST value = new AST();
	AST expr = new AST();
	
	public With(String id, AST value, AST expr) {
		this.id = id;
		this.value = value;
		this.expr = expr;
	}
	
	public String getId() {
		return this.id;
	}
	
	public AST getValue() {
		return this.value;
	}
	
	public AST getExpression() {
		return this.expr;
	}
	
	public String getASTCode() {
		return "(with " + id + " " + value.getASTCode() + " " +expr.getASTCode() + ")";
	}
}
