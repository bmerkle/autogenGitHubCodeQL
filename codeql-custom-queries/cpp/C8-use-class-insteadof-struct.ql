/**  
 * @name Use `class` rather than `struct` if any member is non-public  
 * @description Flags struct declarations that have any non-public (private or protected) members.  
 * @kind problem  
 * @problem.severity warning  
 * @id cpp/non-public-struct  
 */

import cpp

from Struct s
where
  s.fromSource() and
  (
    exists(MemberVariable mv |
      mv.getDeclaringType() = s and
      (mv.hasSpecifier("private") or mv.hasSpecifier("protected"))
    )
    or
    exists(MemberFunction mf |
      mf.getDeclaringType() = s and
      (mf.hasSpecifier("private") or mf.hasSpecifier("protected"))
    )
  )
select s, "The struct '" + s.getName() + "' should be declared as a 'class' because it contains non-public members."