/**
 * @name Example: Find functions longer than 50 lines
 * @description Flags functions whose body exceeds 50 lines.
 *              Replace this with your own custom rule.
 * @kind problem
 * @id custom-cpp/long-function
 * @problem.severity warning
 * @tags maintainability
 *       custom
 */

import cpp

from Function f
where
  f.hasDefinition() and
  f.getMetrics().getNumberOfLinesOfCode() > 50
select f, "Function '" + f.getName() + "' has " +
  f.getMetrics().getNumberOfLinesOfCode().toString() +
  " lines of code (threshold: 50)."
