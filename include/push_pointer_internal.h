
#ifndef PUSH_POINTER_INTERAL_H_
#	define PUSH_POINTER_INTERAL_H_

#include "oolua_userdata.h"
#include "oolua_storage.h"
#include "determin_qualifier.h"

struct lua_State;

namespace OOLUA
{
	/** \cond INTERNAL*/
	namespace INTERNAL
	{
		template<typename Raw, typename TypeMaybeConst>
		void push_pointer_which_has_a_proxy_class(lua_State * vm, TypeMaybeConst * const ptr, Owner owner);

		void if_check_enabled_check_type_is_registered(lua_State* vm, char const* name);
		void set_owner_if_change(Owner owner, Lua_ud* ud);

		template<typename Raw, typename TypeMaybeConst>
		inline void push_pointer_which_has_a_proxy_class(lua_State * vm, TypeMaybeConst * const ptr, Owner owner)
		{
			if_check_enabled_check_type_is_registered(vm, Proxy_class<Raw>::class_name);
			Lua_ud* ud(find_ud(vm, (Raw*)ptr, !!LVD::is_const<TypeMaybeConst>::value));//NOLINT
			if(!ud) ud = add_ptr(vm, (Raw*)ptr, !!(LVD::is_const<TypeMaybeConst>::value), owner);//NOLINT
			else set_owner_if_change(owner, ud);
		}

	} // namespace INTERNAL // NOLINT
	/**\endcond*/
} // namespace OOLUA

#endif
