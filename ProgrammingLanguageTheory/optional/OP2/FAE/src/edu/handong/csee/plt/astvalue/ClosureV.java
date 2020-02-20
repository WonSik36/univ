package edu.handong.csee.plt.astvalue;

import edu.handong.csee.plt.ast.AST;
import edu.handong.csee.plt.dfs.DefrdSub;

public class ClosureV extends ASTValue {
	private String param;
	private AST body;
	private DefrdSub ds;
	
	public ClosureV(String param, AST body, DefrdSub ds) {
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
	
	public DefrdSub getDS() {
		return ds;
	}
	
	@Override
	public String getASTValueCode() {
		return "(closureV " + param + " " + body.getASTCode() + " " + ds.getDSCode() + ")";
	}
}
