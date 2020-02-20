package edu.handong.csee.plt;

import edu.handong.csee.plt.ast.*;
import edu.handong.csee.plt.ast.rcfae.*;
import edu.handong.csee.plt.ast.dfs.*;
import edu.handong.csee.plt.ast.value.*;
import edu.handong.csee.plt.exception.FreeIdentifierException;
import edu.handong.csee.plt.exception.UndefinedASTException;

public class Interpreter {

	public Value interp(AST ast, Dfs ds) {
		
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
		
		if(ast instanceof Mult) {
			Mult mult = (Mult)ast;
			int lhs = Integer.parseInt(((NumV)interp(mult.getLhs(), ds)).getStrNum());
			int rhs = Integer.parseInt(((NumV)interp(mult.getRhs(), ds)).getStrNum());
			NumV res = new NumV(Integer.toString(lhs*rhs));
			
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
			Value aVal = interp(app.getArg(),ds);
			return interp(fVal.getBody(), new ASub(fVal.getParam(), aVal,fVal.getDS()));
		}
		
		if(ast instanceof If0) {
			// [if0   (test-expr then-expr else-expr) 
            // (if (numzero? (interp test-expr ds))(interp then-expr ds)(interp else-expr ds))]
			If0 if0 = (If0)ast;
			NumV testValue = (NumV)interp(if0.getTestExpr(), ds);
			
			if(testValue.getStrNum().equals("0"))
				return interp(if0.getThenExpr(),ds);
			else
				return interp(if0.getElseExpr(),ds);
		}
		
		if(ast instanceof Rec) {
			// [rec  (bound-id func-expr fst-call)
            // (local [(define value-holder (box (numV 198)))
            //         (define new-ds (aRecSub bound-id value-holder ds))]
            //         (begin (set-box! value-holder (interp func-expr new-ds))
            //              (interp fst-call new-ds)))]))
			Rec rec = (Rec)ast;
			Value valueBox = new ClosureV(null,null,null);
			ARecSub newDs = new ARecSub(rec.getId(),valueBox,ds);
			valueBox = (ClosureV)interp(rec.getFuncExpr(),newDs);
			newDs.setValueBox(valueBox);
			
			return interp(rec.getfstCall(), newDs);
		}
		
		throw new UndefinedASTException("Undefined AST: "+ds.getClass().getSimpleName());
	}
	
	public Value lookup(String name, Dfs ds){
		if(ds instanceof MtSub)
			throw new FreeIdentifierException("Free Identifier: "+name);
		
		else if(ds instanceof ASub) {
			ASub aSub = (ASub)ds;
			if(aSub.getName().equals(name))
				return aSub.getValue();
			else
				return lookup(name, aSub.getDS());
			
		}else if(ds instanceof ARecSub) {
			ARecSub aRecSub = (ARecSub)ds;
			if(aRecSub.getName().equals(name)) {
				return aRecSub.getValueBox();
			}else
				return lookup(name, aRecSub.getDS());
		}
		
		throw new UndefinedASTException("Undefined AST: "+ds.getClass().getSimpleName());
	}
}
