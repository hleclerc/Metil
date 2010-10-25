/*! 
\page History History

The Metil project started in 2005 ...
-# LMTpp (C++/Python)
    - Principles: It was written as an "active library" heavily relying on the <tt>template</tt> keyword of the C++. To help manipulation formulation and finite elements, tools for symbolic code generation has been developped. A lot of work has been done on optimization to be competitive in front of commercial platforms.
    - Main drawbacks: the heavy use of fhe <tt>template</tt> keyword leads to long compilation duration time, and lacks dynamisms. For example: a symetric matrix cannot become non-symetric, ...
-# Metil Language
    - Principles: to alleviate the syntax heaviness and the fact that a lot of users from the LMT-Cachan has complained about the pain of programming in C++ (with templates), a python-like language has been designed. This language is devoted to expressivity and code generation. Interfaces has been developped such as integration of C++ code was fully automatic, allowing the use of virtually every C++ or C libraries.
    - Main drawbacks: using and developping a new language in the context of an applied mechanics laboratory is hard to defend.
-# Metil (full C++)
 - Principles: this new platform has been developped in order to use the only C++ language. Ease-of-use has been a fundamental concern since the ground-up, with sometimes some compromises on speed.

Currently metil is mainly used in LMT-Cachan (ENS de Cachan/CNRS/UPMC/PRES UniverSud Paris) and maintained by the LMT's software team. It is released under the LGPLv2 License.
*/
