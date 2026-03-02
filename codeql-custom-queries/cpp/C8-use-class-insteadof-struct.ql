/**  
 * @name Use `class` rather than `struct` if any member is non-public  
 * @description Flags struct declarations that have any non-public (private or protected) members.  
 * @kind problem  
 * @problem.severity warning  
 * @id cpp/non-public-struct  
 */

import cpp

from Struct s, Member m
where
  // 1. Find members belonging to the struct
  m = s.getAMember() and
  // 2. Check if the member is NOT public (i.e., private or protected)
  not m.isPublic() and
  // 3. Ensure we aren't looking at compiler-generated internal members
  not m.isCompilerGenerated()
select s, "The struct '" + s.getName() + "' should be declared as a 'class' because it contains non-public members (e.g., '" + m.getName() + "')."