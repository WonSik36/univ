package edu.handong.csee.plt.ast.rbmrcfae;

public class If0 implements RBMRCFAE {
	RBMRCFAE testExpr;
	RBMRCFAE thenExpr;
	RBMRCFAE elseExpr;
	
	public If0(RBMRCFAE testExpr, RBMRCFAE thenExpr, RBMRCFAE elseExpr) {
		this.testExpr = testExpr;
		this.thenExpr = thenExpr;
		this.elseExpr = elseExpr;
	}
	
	public RBMRCFAE getTestExpr() {
		return this.testExpr;
	}
	
	public RBMRCFAE getThenExpr() {
		return this.thenExpr;
	}
	
	public RBMRCFAE getElseExpr() {
		return this.elseExpr;
	}
	
	@Override
	public String getASTCode() {
		return "(if0 "+testExpr.getASTCode()+" "+thenExpr.getASTCode()+" "+elseExpr.getASTCode()+")";
	}

}
