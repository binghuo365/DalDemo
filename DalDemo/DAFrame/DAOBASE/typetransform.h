#ifndef _DAF_TYPE_TRANSFORM_H_
#define _DAF_TYPE_TRANSFORM_H_

#include <string>
#include "publicdef.h"

namespace DAFrame
{
	
	static const int CDF_M_BUFF_LEN		=	128  ;
	
	class CTypeTransform  
	{
	private:
		char buf[CDF_M_BUFF_LEN];	
	public:
		CTypeTransform(int v);
		CTypeTransform(float v);
		CTypeTransform(double v);
		CTypeTransform(unsigned int v);
		CTypeTransform(short v);
		CTypeTransform(bool v);
		CTypeTransform(long64_t v);
		
	public:
		std::string toString();
		virtual ~CTypeTransform();
		
	};
}

#define  ToStr( X ) CTypeTransform(X).toString()






#endif // !defined(AFX_TYPETRANSFORM_H__FF07E4BE_22F6_4DAB_BE11_ED625DA883D5__INCLUDED_)
