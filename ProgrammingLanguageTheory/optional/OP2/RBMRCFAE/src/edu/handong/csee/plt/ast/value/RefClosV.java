package edu.handong.csee.plt.ast.value;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.ast.dfs.Dfs;

public class RefClosV implements Value {
	private String param;
	private AST body;
	private Dfs ds;
	
	public RefClosV(String param, AST body, Dfs ds) {
		this.param = param;
		this.body = body;
		this.ds = ds;
	}
	
	public String getParam() {
		return param;
	}
	
	public AST getBody() {
		return body;
	}
	
	public Dfs getDS() {
		return ds;
	}
	
	@Override
	public String getASTCode() {
		return "(refclosV " + param + " " + body.getASTCode() + " " + ds.getASTCode() + ")";
	}
}
