package edu.handong.csee.plt.ast.rbmrcfae;

public class App implements RBMRCFAE {
	RBMRCFAE ftn;
	RBMRCFAE arg;
	
	public App(RBMRCFAE ftn, RBMRCFAE arg){
		this.ftn = ftn;
		this.arg = arg;
	}
	
	public RBMRCFAE getFtn() {
		return ftn;
	}
	
	public RBMRCFAE getArg() {
		return arg;
	}
	
	@Override
	public String getASTCode() {
		return "(app " + ftn.getASTCode() + " " + arg.getASTCode() + ")";
	}
	
}
