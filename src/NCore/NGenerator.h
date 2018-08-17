// � 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_GENERATOR_H_
#define _N_GENERATOR_H_

#include "NObject.h"
#include "NRegistry.h"
#include "NGeneratorArgs.h"

namespace NLib
{
	class NAPI NGenerator : public NObject
	{
	protected:
		int _line;
	public:
		NGenerator() { rewind(); }
		void rewind() { _line = 0; } // restart the generator

	private:
		NGenerator(const NGenerator&); // non-copyable
		NGenerator& operator=(const NGenerator&); // non-assignable
	};

#define $generator(NAME) struct NAME : public generator::instance

#define $emit(T)            bool operator()(T& _rv) { switch(_line) { case 0:;
#define $emit2(T1,T2)       bool operator()(T1& _rv1, T2& _rv2) { switch(_line) { case 0:;
#define $emit3(T1,T2,T3)    bool operator()(T1& _rv1, T2& _rv2, T3& _rv3 ) { switch(_line) { case 0:;
#define $emit4(T1,T2,T3,T4) bool operator()(T1& _rv1, T2& _rv2, T3& _rv3, T4& _rv4 ) { switch(_line) { case 0:;

#define $yield(V)            { _line=__LINE__; _rv = (V); return true; case __LINE__: _line=__LINE__; }
#define $yield2(V1,V2)       { _line=__LINE__; _rv1 = (V1); _rv2 = (V2); return true; case __LINE__: _line=__LINE__; }
#define $yield3(V1,V2,V3)    { _line=__LINE__; _rv1 = (V1); _rv2 = (V2); _rv3 = (V3); return true; case __LINE__: _line=__LINE__; }  
#define $yield4(V1,V2,V3,V4) { _line=__LINE__; _rv1 = (V1); _rv2 = (V2); _rv3 = (V3); _rv4 = (V4); return true; case __LINE__: _line=__LINE__; }
#define $stop  } _line = 0; return false; }

}

#endif // !_W_GENERATOR_H_


	