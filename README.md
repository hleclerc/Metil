Here is the game:
* C++ is a fabulous language, notably for numerical analysis where performance and memory usage matter
* but we need multiple dispatch (e.g. binary operations between matrices, symbolic operations, ...) without performance penalty and heavy or clumsy code
* we like types, we like to use types to store information (e.g. a symbol Pi, an operation Add_is to say that the first operand is an immediate number, ...).
  * It leads to a lot of types... but we dot not need all of them in all sort of applications (e.g. evey type of matrices, fields, meshes... there are some people in the world that actually don't care about meshes :) ), meaning that dynamic loading should be automatic/transparent.
  * Code for similar types should be factorized. Il would be great to have a possible stage of code generation for given types and operations.

Thus, Metil is an attempt to solve theses issues (in the context of numerical analysis).

The pros:
- performance is very good: 
  * binary dispatching is ~5.5x faster than the "2 consecutive unary dispatch" approach
  * code generation (+ information on types rather than in attributes) enable very significant optimizations (a kind of deep inlining, with rich informations)
- the resulting codes are light, fast to launch (even if we have a lot of types and a lot of n-ary methods)
- it is *way more* convenient than the static polymorphism approach (template meta-programming, ...), for a very comparable performance gain in the applications we have tested so far. It can actually lead to faster code because we use give up with static polymorphism (e.g. when contiuation passing style is not convenient, ...).

The cons:
- when it comes to create new objects or new methods... well... it seems to be far from pratical...
