#ifndef EXPOSE_HEIRARCHY_H_
#	define EXPOSE_HEIRARCHY_H_

#include "oolua.h"
#include "cpp_hierarchy.h"

#define OOLUA_TEST_VA_ARGS 1

OOLUA_CLASS_NO_BASES(Abstract1)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
	OOLUA_MEM_FUNC_0(void,func1)

#if OOLUA_TEST_VA_ARGS == 1
	TEST_OOLUA_MEM_FUNC(void,virtualVoidParam3Int,int,int,int)

#else
	OOLUA_MEM_FUNC_3(void,virtualVoidParam3Int,int,int,int)
#endif

OOLUA_CLASS_END


OOLUA_CLASS_NO_BASES(Abstract2)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
	OOLUA_MEM_FUNC_0(void,func2_1)
OOLUA_CLASS_END


OOLUA_CLASS_NO_BASES(Abstract3)
	OOLUA_TYPEDEFS Abstract OOLUA_END_TYPES
	OOLUA_MEM_FUNC_0(void,func3_1)
OOLUA_CLASS_END

#if OOLUA_TEST_VA_ARGS == 1
TEST_OOLUA_CLASS_WITH_BASES(Derived1Abstract1,Abstract1)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

#else

OOLUA_CLASS(Derived1Abstract1) : public Proxy_class<Abstract1>
	OOLUA_BASIC
	OOLUA_NO_TYPEDEFS
	OOLUA_BASES_START Abstract1 OOLUA_BASES_END
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END
#endif

#if OOLUA_TEST_VA_ARGS == 1
TEST_OOLUA_CLASS_WITH_BASES(TwoAbstractBases,Abstract1,Abstract2)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

#else
OOLUA_CLASS(TwoAbstractBases) : public Proxy_class<Abstract1>, public Proxy_class<Abstract2>
	OOLUA_BASIC
	OOLUA_NO_TYPEDEFS
	OOLUA_BASES_START Abstract1,Abstract2 OOLUA_BASES_END
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END
#endif

#if OOLUA_TEST_VA_ARGS == 1
TEST_OOLUA_CLASS_WITH_BASES(DerivedFromTwoAbstractBasesAndAbstract3,TwoAbstractBases,Abstract3)
	OOLUA_NO_TYPEDEFS
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END

#else
OOLUA_CLASS(DerivedFromTwoAbstractBasesAndAbstract3) : public Proxy_class<TwoAbstractBases>, public Proxy_class<Abstract3>
	OOLUA_BASIC
	OOLUA_NO_TYPEDEFS
	OOLUA_BASES_START TwoAbstractBases,Abstract3 OOLUA_BASES_END
	OOLUA_ONLY_DEFAULT_CONSTRUCTOR
OOLUA_CLASS_END
#endif

namespace BASE_HELPERS
{
	//NOTE: Base class order is defined and used in OOLUA code.
	//Immediate bases come first in the order defined in the OOLUA_BASES_START to OOLUA_BASES_END block
	//then the bases of these base classes again in the order they were defined.
	inline std::vector<std::string>allBasesOfDerivedFromTwoAbstractBasesAndAbstract3()
	{
		std::vector<std::string> v;
		v.push_back("TwoAbstractBases");
		v.push_back("Abstract3");
		v.push_back("Abstract1");
		v.push_back("Abstract2");
		return v;
	}

	//Order for roots is defined (due to the nature in which the list is generated in OOLUA code), yet never used.
	//A root base is a base of class which has no bases itself.
	//If a class which is registered has no bases then it is not a root to itself yet can be a root for other classes.
	inline std::vector<std::string> rootBasesOfDerivedFromTwoAbstractBasesAndAbstract3()
	{
		std::vector<std::string> v;
		v.push_back("Abstract3");
		v.push_back("Abstract1");
		v.push_back("Abstract2");
		return v;
	}
}
#endif
