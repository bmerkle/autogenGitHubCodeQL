/**
 * @name Incomplete set of overloaded operators
 * @description Flags classes that overload some operators but not a complete,
 *              related set.  For example a class that defines `operator<` but
 *              not `operator==`, or `operator-` but not `operator+`.
 *              This is inspired by the T.21 guideline: "Require a complete
 *              set of operations for a concept."
 * @kind problem
 * @problem.severity warning
 * @id cpp/incomplete-operator-set
 * @tags maintainability
 *       readability
 */

import cpp

/*
 * Helper: does the class (or a base) define a member operator with the
 * given name?  Operator names in CodeQL use the C++ spelling, e.g.
 * "operator<", "operator==".
 */
predicate hasOperator(Class c, string op) {
  exists(MemberFunction mf |
    mf.getDeclaringType() = c and
    mf.getName() = op
  )
}

/*
 * Comparison completeness:
 *   If any ordering operator (<, >, <=, >=) is defined,
 *   then == and != should also be defined.
 */
predicate hasAnyOrdering(Class c) {
  hasOperator(c, "operator<") or
  hasOperator(c, "operator>") or
  hasOperator(c, "operator<=") or
  hasOperator(c, "operator>=")
}

predicate missingEquality(Class c) {
  hasAnyOrdering(c) and
  (not hasOperator(c, "operator==") or not hasOperator(c, "operator!="))
}

/*
 * Arithmetic completeness:
 *   If operator- is defined, operator+ should be too (and vice-versa).
 */
predicate missingArithmeticCounterpart(Class c) {
  (hasOperator(c, "operator-") and not hasOperator(c, "operator+"))
  or
  (hasOperator(c, "operator+") and not hasOperator(c, "operator-"))
}

from Class c, string reason
where
  c.fromSource() and
  (
    missingEquality(c) and reason = "defines ordering operators but is missing operator== or operator!="
    or
    missingArithmeticCounterpart(c) and reason = "defines operator+ or operator- but not both"
  )
select c, "Class '" + c.getName() + "' has an incomplete set of operators: " + reason + "."
