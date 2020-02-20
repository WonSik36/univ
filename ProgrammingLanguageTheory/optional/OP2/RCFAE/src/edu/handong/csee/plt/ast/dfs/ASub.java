package edu.handong.csee.plt.ast.dfs;

import edu.handong.csee.plt.ast.value.Value;

public class ASub implements Dfs {
	private String name;
	private Value value;
	private Dfs ds;
	
	public ASub(String name, Value value, Dfs ds) {
		this.name = name;
		this.value = value;
		this.ds = ds;
	}
	
	public String getName() {
		return name;
	}
	
	public Value getValue() {
		return value;
	}
	
	public Dfs getDS() {
		return ds;
	}
	
	@Override
	public String getASTCode() {
		return "(aSub " + name + " " + value.getASTCode() + " " + ds.getASTCode() + ")";
	}
	
}
