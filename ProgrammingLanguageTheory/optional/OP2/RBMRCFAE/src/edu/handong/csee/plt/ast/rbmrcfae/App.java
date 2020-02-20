package edu.handong.csee.plt.ast.rbmrcfae;

import edu.handong.csee.plt.ast.AST;

public class App implements RBMRCFAE {
	AST ftn;
	AST arg;
	
	public App(AST ftn, AST arg){
		this.ftn = ftn;
		this.arg = arg;
	}
	
	public AST getFtn() {
		return ftn;
	}
	
	public AST getArg() {
		return arg;
	}
	
	@Override
	public String getASTCode() {
		return "(app " + ftn.getASTCode() + " " + arg.getASTCode() + ")";
	}
	
}
