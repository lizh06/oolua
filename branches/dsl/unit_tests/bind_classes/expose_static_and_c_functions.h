#ifndef EXPOSE_STATIC_AND_C_FUNCTIONS_H_
#	define EXPOSE_STATIC_AND_C_FUNCTIONS_H_

#include "oolua.h"
#include "cpp_static_and_c_functions.h"

/*[ClassStaticFunctionExpose]*/
OOLUA_PROXY(ClassHasStaticFunction)
	OOLUA_TAGS(No_public_constructors)
	OOLUA_SFUNC(returns_input)
OOLUA_PROXY_END
/*[ClassStaticFunctionExpose]*/

int oolua_ClassHasStaticFunction_static_function(lua_State* l);
int oolua_ClassHasStaticFunction_static_function_int(lua_State* l);

#endif