package edu.handong.csee.plt.ast.dfs;

import edu.handong.csee.plt.ast.value.Value;

public class ARecSub implements Dfs {
	private String name;
	private Value valueBox;
	private Dfs ds;
	
	public ARecSub(String name, Value valueBox, Dfs ds) {
		this.name = name;
		this.valueBox = valueBox;
		this.ds = ds;
	}
	
	public String getName() {
		return name;
	}
	
	public Value getValueBox() {
		return valueBox;
	}
	
	public void setValueBox(Value valueBox) {
		this.valueBox = valueBox;
	}
	
	public Dfs getDS() {
		return ds;
	}
	
	@Override
	public String getASTCode() {
		return "(aSub " + name + " " + valueBox.getASTCode() + " " + ds.getASTCode() + ")";
	}
	
}
