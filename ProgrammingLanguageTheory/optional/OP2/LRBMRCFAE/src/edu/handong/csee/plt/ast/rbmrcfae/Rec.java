package edu.handong.csee.plt.ast.rbmrcfae;

public class Rec implements RBMRCFAE {
	String id;
	RBMRCFAE funcExpr;
	RBMRCFAE fstCall;
	
	public Rec(String id, RBMRCFAE funcExpr, RBMRCFAE fstCall) {
		this.id = id;
		this.funcExpr = funcExpr;
		this.fstCall = fstCall;
	}
	
	public String getId() {
		return this.id;
	}
	
	public RBMRCFAE getFuncExpr() {
		return this.funcExpr;
	}
	
	public RBMRCFAE getfstCall() {
		return this.fstCall;
	}
	
	@Override
	public String getASTCode() {
		return "(rec "+id+" "+funcExpr.getASTCode()+" "+fstCall.getASTCode()+")";
	}
}
