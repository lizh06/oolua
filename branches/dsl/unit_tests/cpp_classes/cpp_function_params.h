#ifndef CPP_FUNCTION_PARAMS_H_
#	define CPP_FUNCTION_PARAMS_H_


#	include "oolua_tests_pch.h"
#	include "gmock/gmock.h"

template<typename Specialisation , typename ParamType>
class FunctionParamType
{
public:
	virtual ~FunctionParamType(){}
	/**[ValueParam]*/
	virtual void value(ParamType) = 0;
	/**[ValueParam]*/

	/**[PtrParam]*/
	virtual void ptr(ParamType*) = 0;
	/**[PtrParam]*/

	/**[RefParam]*/
	virtual void ref(ParamType&)=0;
	/**[RefParam]*/

	/**[RefPtrParam]*/
	virtual void refPtr(ParamType*&) = 0;
	/**[RefPtrParam]*/

	virtual void constant(ParamType const) = 0;
	virtual void refConst(ParamType const &) = 0;
	virtual void ptrConst(ParamType const *) = 0;
	/**[RefPtrConstParam]*/
	virtual void refPtrConst(ParamType const* &) = 0;
	/**[RefPtrConstParam]*/
	virtual void constPtr(ParamType * const) = 0;
	virtual void refConstPtr(ParamType * const&) = 0;
	virtual void constPtrConst(ParamType const * const) = 0;
	virtual void refConstPtrConst(ParamType const * const &) = 0;
	
	virtual void twoRefs(ParamType &,ParamType &) = 0;
};

template<typename Specialisation , typename ParamType>
class MockFunctionParamType : public FunctionParamType<Specialisation,ParamType>
{
public:
	MOCK_METHOD1_T(value,void (ParamType));
	MOCK_METHOD1_T(ptr,void (ParamType*));
	MOCK_METHOD1_T(ref,void (ParamType&));
	MOCK_METHOD1_T(refPtr,void (ParamType*&));
	
	MOCK_METHOD1_T(constant,void (ParamType const));
	MOCK_METHOD1_T(refConst,void (ParamType const &));
	MOCK_METHOD1_T(ptrConst,void (ParamType const *));
	MOCK_METHOD1_T(refPtrConst,void (ParamType const* &));
	MOCK_METHOD1_T(constPtr,void (ParamType * const));
	MOCK_METHOD1_T(refConstPtr,void (ParamType * const&));
	MOCK_METHOD1_T(constPtrConst,void(ParamType const * const));
	MOCK_METHOD1_T(refConstPtrConst,void (ParamType const * const &));
	MOCK_METHOD2_T(twoRefs,void(ParamType &,ParamType &));
};

#endif