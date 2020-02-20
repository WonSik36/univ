package edu.handong.csee.plt.dfs;

import edu.handong.csee.plt.astvalue.ASTValue;

public class ASub extends DefrdSub {
	private String name;
	private ASTValue value;
	private DefrdSub ds;
	
	public ASub(String name, ASTValue value, DefrdSub ds) {
		this.name = name;
		this.value = value;
		this.ds = ds;
	}
	
	public String getName() {
		return name;
	}
	
	public ASTValue getValue() {
		return value;
	}
	
	public DefrdSub getDS() {
		return ds;
	}
	
	@Override
	public String getDSCode() {
		return "(aSub " + name + " " + value.getASTValueCode() + " " + ds.getDSCode() + ")";
	}
}
