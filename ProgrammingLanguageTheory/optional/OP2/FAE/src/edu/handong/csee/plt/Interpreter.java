package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.*;
import edu.handong.csee.plt.astvalue.*;
import edu.handong.csee.plt.dfs.*;

public class Interpreter {

	public ASTValue interp(AST ast, DefrdSub ds) {
		
		if(ast instanceof Num) {
			Num num = ((Num)ast); 
			return new NumV(num.getStrNum());
		}
		
		if(ast instanceof Add) {
			Add add = (Add)ast;
			int lhs = Integer.parseInt(((NumV)interp(add.getLhs(), ds)).getStrNum());
			int rhs = Integer.parseInt(((NumV)interp(add.getRhs(), ds)).getStrNum());
			NumV res = new NumV(Integer.toString(lhs+rhs));
			
			return res;
		}
		
		if(ast instanceof Sub) {
			Sub sub = (Sub)ast;
			int lhs = Integer.parseInt(((NumV)interp(sub.getLhs(), ds)).getStrNum());
			int rhs = Integer.parseInt(((NumV)interp(sub.getRhs(), ds)).getStrNum());
			NumV res = new NumV(Integer.toString(lhs-rhs));
			
			return res;
		}
		
		
		if(ast instanceof Id) {
			Id id = (Id)ast;
			return lookup(id.getId(),ds);
		}
		
		if(ast instanceof Fun) {
			Fun fun = (Fun)ast;
			return new ClosureV(fun.getParam(), fun.getBody(), ds);
		}
		
		if(ast instanceof App) {
			App app = (App)ast;
			ClosureV fVal = (ClosureV)interp(app.getFtn(),ds);
			ASTValue aVal = interp(app.getArg(),ds);
			return interp(fVal.getBody(), new ASub(fVal.getParam(), aVal,fVal.getDS()));
		}
		
		throw new RuntimeException("Undefined AST");
	}
	
	public ASTValue lookup(String name, DefrdSub ds) {
		if(ds instanceof MtSub)
			throw new RuntimeException("lookup: free identifier");
		if(ds instanceof ASub) {
			ASub aSub = (ASub)ds;
			if(aSub.getName().equals(name))
				return aSub.getValue();
			else
				return lookup(name, aSub.getDS());
		}
		throw new RuntimeException("Undefined DefrdSub");
	}
}
