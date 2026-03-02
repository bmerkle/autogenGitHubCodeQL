/**  
 * @name Incomplete operation sets in C++ concepts  
 * @description Flags concepts whose `requires`-expressions use certain operations  
 *              (like `-` or `<`) without also requiring a corresponding "complete set"  
 *              of related operations (for example, `+` for `-`, or `==`/`!=` for `<`).  
 * @kind problem  
 * @problem.severity warning  
 * @id cpp/incomplete-concept-operation-set  
 * @tags maintainability readability  
 */

import cpp  
import semmle.code.cpp.Concept  // Provides Concept, RequiresExpr, SimpleRequirementExpr, etc. <a href="2e998477-8030-4bb2-aaf8-cac91b445fbb" class="citation">[4.1]</a> <a href="70d3939e-99a1-4de3-ab4d-6e5776ed6695" class="citation">[4.5]</a> <a href="77d861b7-ca5b-4ad7-b36a-ca863bdb3887" class="citation">[4.6]</a>

/**  
 * Helper: return true if `e` syntactically uses the given operator spelling.  
 *  
 * This is a simple textual/AST-based heuristic; it does not try to resolve overloads.  
 */  
predicate exprUsesOperator(Expr e, string op) {  
  exists(OperatorExpr oe |  
    oe = e and  
    oe.getOperator() = op  
  )  
}

/**  
 * A simple requirement whose expression uses a given operator.  
 */  
class RequirementUsingOp extends SimpleRequirementExpr {  
  string op;

  RequirementUsingOp() {  
    exists(string o |  
      op = o and  
      exprUsesOperator(this.getExpr(), o)  
    )  
  }  
}

/**  
 * A concept (or other declaration) with an associated requires-expression.  
 */  
class HasRequiresExpr extends Concept {  
  RequiresExpr getRequires() {  
    result = any(RequiresExpr re | re = this.getARequiresExpr())  
  }  
}

/**  
 * Does `re` require the given operator somewhere in its simple requirements?  
 */  
predicate requiresOp(RequiresExpr re, string op) {  
  exists(SimpleRequirementExpr sr |  
    sr = re.getARequirement() and  
    exprUsesOperator(sr.getExpr(), op)  
  )  
}

/**  
 * Arithmetic-like concepts:  
 *  - If `-` is required but `+` is not, we consider the set incomplete.  
 *  - You can expand to check the full set (+,-,*,/, +=, -=, *=, /=) if desired.  
 */  
predicate isIncompleteArithmetic(RequiresExpr re) {  
  requiresOp(re, "-") and  
  not requiresOp(re, "+")  
}

/**  
 * Comparable-like concepts:  
 *  - If any of the ordering operators (<, >, <=, >=) is required  
 *    but equality (`==` and `!=`) is not, we consider the set incomplete.  
 */  
predicate isIncompleteComparable(RequiresExpr re) {  
  (  
    requiresOp(re, "<") or  
    requiresOp(re, ">") or  
    requiresOp(re, "<=") or  
    requiresOp(re, ">=")  
  ) and  
  (  
    not requiresOp(re, "==") or  
    not requiresOp(re, "!=")  
  )  
}

/**  
 * A concept whose requires-expression appears to use an incomplete set of operations.  
 */  
from HasRequiresExpr c, RequiresExpr re  
where  
  re = c.getRequires() and  
  (isIncompleteArithmetic(re) or isIncompleteComparable(re))  
select re,  
  "This concept uses an incomplete set of operations (" +  
  (isIncompleteArithmetic(re) ? "arithmetic" : "comparison") +  
  "). Consider requiring the full, meaningful set of related operators."  
