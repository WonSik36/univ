package edu.handong.csee.plt.ast.rcfae;

public class If0 implements RCFAE {
	RCFAE testExpr;
	RCFAE thenExpr;
	RCFAE elseExpr;
	
	public If0(RCFAE testExpr, RCFAE thenExpr, RCFAE elseExpr) {
		this.testExpr = testExpr;
		this.thenExpr = thenExpr;
		this.elseExpr = elseExpr;
	}
	
	public RCFAE getTestExpr() {
		return this.testExpr;
	}
	
	public RCFAE getThenExpr() {
		return this.thenExpr;
	}
	
	public RCFAE getElseExpr() {
		return this.elseExpr;
	}
	
	@Override
	public String getASTCode() {
		return "(if0 "+testExpr.getASTCode()+" "+thenExpr.getASTCode()+" "+elseExpr.getASTCode()+")";
	}

}
