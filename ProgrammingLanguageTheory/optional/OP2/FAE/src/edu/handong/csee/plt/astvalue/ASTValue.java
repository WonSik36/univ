package edu.handong.csee.plt.astvalue;

import edu.handong.csee.plt.ast.*;
import edu.handong.csee.plt.dfs.*;

public class ASTValue {

	public static void main(String[] args) {
		// (closureV 'x (add (id 'x) (id 'y)) (aSub 'y (numV 3) (mtSub)))
		ASTValue v = new ClosureV("x", new Add(new Id("x"), new Id("y")), new ASub("y", new NumV("3"), new MtSub()));
		System.out.println(v.getASTValueCode());
	}
	
	public String getASTValueCode() {
		String astValueCode="";
		if(this instanceof NumV)
			astValueCode = ((NumV)this).getASTValueCode();
		
		if(this instanceof ClosureV)
			astValueCode = ((ClosureV)this).getASTValueCode();
		

		return astValueCode;
	}
}
