package edu.handong.csee.plt.ast.value;

import edu.handong.csee.plt.ast.dfs.Dfs;
import edu.handong.csee.plt.ast.rbmrcfae.RBMRCFAE;
import edu.handong.csee.plt.ast.store.Store;

public class ExprV implements Value {
	private RBMRCFAE expr;
	private Dfs ds;
	private Store st;
	private Value v;
	
	public ExprV(RBMRCFAE expr, Dfs ds, Store st, Value v) {
		this.expr = expr;
		this.ds = ds;
		this.st = st;
		this.v = v;
	}
	
	public RBMRCFAE getExpr() {
		return expr;
	}
	
	public Dfs getDs() {
		return ds;
	}
	
	public Store getSt() {
		return st;
	}
	
	public Value getValue() {
		return v;
	}
	
	public void setValue(Value v) {
		this.v = v;
	}
	
	@Override
	public String getASTCode() {
		return "(exprV "+expr.getASTCode()+" "+ds.getASTCode()+" "+v.getASTCode()+")";
	}

}
