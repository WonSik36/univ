package edu.handong.csee.plt.ast.dfs;

import edu.handong.csee.plt.ast.value.Value;

public class ASub implements Dfs {
	private String name;
	private int adr;
	private Dfs ds;
	
	public ASub(String name, int adr, Dfs ds) {
		this.name = name;
		this.adr = adr;
		this.ds = ds;
	}
	
	public String getName() {
		return name;
	}
	
	public int getAdr() {
		return adr;
	}
	
	public Dfs getDS() {
		return ds;
	}
	
	@Override
	public String getASTCode() {
		return "(aSub " + name + " " + adr + " " + ds.getASTCode() + ")";
	}
	
}
