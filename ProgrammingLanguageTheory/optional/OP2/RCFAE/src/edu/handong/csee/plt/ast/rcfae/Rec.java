package edu.handong.csee.plt.ast.rcfae;

public class Rec implements RCFAE {
	String id;
	RCFAE funcExpr;
	RCFAE fstCall;
	
	public Rec(String id, RCFAE funcExpr, RCFAE fstCall) {
		this.id = id;
		this.funcExpr = funcExpr;
		this.fstCall = fstCall;
	}
	
	public String getId() {
		return this.id;
	}
	
	public RCFAE getFuncExpr() {
		return this.funcExpr;
	}
	
	public RCFAE getfstCall() {
		return this.fstCall;
	}
	
	@Override
	public String getASTCode() {
		return "(rec "+id+" "+funcExpr.getASTCode()+" "+fstCall.getASTCode()+")";
	}
}
