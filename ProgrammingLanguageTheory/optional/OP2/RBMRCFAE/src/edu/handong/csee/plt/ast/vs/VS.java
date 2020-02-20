package edu.handong.csee.plt.ast.vs;

import edu.handong.csee.plt.ast.store.Store;
import edu.handong.csee.plt.ast.value.Value;

public class VS implements ValueStore {
	private Value value;
	private Store st;
	
	public VS(Value value, Store st) {
		this.value = value;
		this.st = st;
	}
	
	public Value getValue() {
		return value;
	}
	
	public Store getSt() {
		return st;
	}
	
	@Override
	public String getASTCode() {
		return "(v*s "+value.getASTCode()+" "+st.getASTCode()+")";
	}

}
