/*
 * <RCFAE> ::= <num>
 *          | {+ <RCFAE> <RCFAE>}
 *          | {- <RCFAE> <RCFAE>}
 *          | {* <RCFAE> <RCFAE>}
 *          | <id>
 *          | {fun {<id} <RCFAE>}
 *          | {<RCFAE> <RCFAE>}
 *          | {if0 <RCFAE> <RCFAE> RCFAE>}
 *          | {rec {<id> <RCFAE>} <RCFAE>}
*/

package edu.handong.csee.plt.ast;

public interface AST {
	// it isn't used
	public String getASTCode();
}

