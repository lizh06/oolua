///////////////////////////////////////////////////////////////////////////////
///  @file lua_table.h
///  Wrapper around a table in Lua which allows quick and easy access.
///  @author Liam Devine
///  @email
///  See http://www.liamdevine.co.uk for contact details.
///  @licence 
///  See licence.txt for more details. \n 
///////////////////////////////////////////////////////////////////////////////
#ifndef LUA_TABLE_H_
#	define LUA_TABLE_H_

#	include "lua_includes.h"
#	include "fwd_push_pull.h"
#	include "lua_ref.h"
#	include <string>

namespace OOLUA
{
	///////////////////////////////////////////////////////////////////////////////
	///  @class Lua_table
	///  Wrapper around a table in Lua which allows quick and easy access.
	///
	///  @remarks
	///  Any value can be retrieved or set from the table via the use of the template
	///  member function. If the value asked for is not the correct type located
	///  in the position then the functions used throw an error.
	///  The functions guarantee that the Lua stack after operations is restored
	///  to the state when entered.
	///////////////////////////////////////////////////////////////////////////////
	class Lua_table
	{
	public:
		Lua_table();
		Lua_table(lua_State*  const lua,std::string const& name);
		void bind_script(lua_State*  const lua);
		void set_table(std::string const& name);
		Lua_table& operator =(Lua_table const& /*rhs*/);//unimplemented
		Lua_table(Lua_table const& /*rhs*/);//unimplemented

		template<typename T,typename T1>bool safe_at(T const& key,T1& value)
		{
			//record the stack size as we want to put the stack into the 
			//same state that it was before entering here
			//int init_stack_size = lua_gettop(m_lua);
			int const init_stack_size = initail_stack_size();
			if(!get_table())return false;
			push2lua(m_lua,key);
			//table is now at -2 (key is at -1). lua_gettable now pops the key off
			//the stack and then puts the data found at the key location on the stack
			lua_gettable(m_lua, -2);
			if(lua_type(m_lua,-1) == LUA_TNIL )
			{
				restore_stack(init_stack_size);
//#if defined OOLUA_EXCEPTIONS
//				throw std::out_of_range("value is not present in table");
//#else
				return false;
//#endif
			}
			pull2cpp(m_lua, value);
			restore_stack(init_stack_size);

			return true;
		}
		//no error checking
		//undefined if lua is null or (table or key is invalid) or value is not correct type
		template<typename T,typename T1>T1& at(T const& key,T1& value)
		{
			//int const init_stack_size = initail_stack_size();
			get_table();//table
			push2lua(m_lua,key);//table key
			lua_gettable(m_lua, -2);//table value
			pull2cpp(m_lua, value);//table
			lua_pop(m_lua,1);
			return value;
		}

		template<typename T,typename T1>void set_value(T const& key,T1 const& value)
		{
			//record the stack size as we want to put the stack into the 
			//same state that it was before entering here
			//int init_stack_size = lua_gettop(m_lua);
			int const init_stack_size = initail_stack_size();
			if(!get_table())return;
			push2lua(m_lua,key);
			//table is now at -2 (key is at -1). 
			//push the new value onto the stack
			push2lua(m_lua,value);
			//table is not at -3 set the table
			lua_settable(m_lua,-3);

			restore_stack(init_stack_size);
		}
		template<typename T>void remove_value(T const& key)
		{
			//record the stack size as we want to put the stack into the 
			//same state that it was before entering here
			//int init_stack_size = lua_gettop(m_lua);
			int const init_stack_size = initail_stack_size();
			if(!get_table())return;
			push2lua(m_lua,key);
			//table is now at -2 (key is at -1). 
			//push the new value onto the stack
			lua_pushnil(m_lua);
			//table is not at -3 set the table
			lua_settable(m_lua,-3);

			restore_stack(init_stack_size);
		}
		bool valid()const;
		void set_ref(lua_State* const lua,int const& ref);
		typedef void(*traverse_do_function)(lua_State*);
		void traverse(traverse_do_function do_);
		bool get_table()const;
		void swap(Lua_table & rhs);
	private:
		void restore_stack(int const & init_stack_size)const;
		int initail_stack_size()const;
		lua_State* m_lua;
		Lua_table_ref m_table_ref;
	};

}

#endif

//==============================
//traversal
//==============================
//int lua_next (lua_State *L, int index);
//
//Pops a key from the stack, and pushes a key-value pair from the table at the given 
//index (the "next" pair after the given key). If there are no more elements in the 
//table, then lua_next returns 0 (and pushes nothing).
//
//A typical traversal looks like this:
//
//     /* table is in the stack at index 't' */
//     lua_pushnil(L);  /* first key */
//     while (lua_next(L, t) != 0) {
//       /* uses 'key' (at index -2) and 'value' (at index -1) */
//       printf("%s - %s\n",
//              lua_typename(L, lua_type(L, -2)),
//              lua_typename(L, lua_type(L, -1)));
//       /* removes 'value'; keeps 'key' for next iteration */
//       lua_pop(L, 1);
//     }
//
//While traversing a table, do not call lua_tolstring directly on a key, unless you 
//know that the key is actually a string. Recall that lua_tolstring changes the 
//value at the given index; this confuses the next call to lua_next. 
//*/

