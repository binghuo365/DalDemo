#include "typetransform.h"

#include "stdio.h"

using namespace DAFrame;


CTypeTransform::CTypeTransform(int v)
{
	sprintf(this->buf,"%d",v);
}

CTypeTransform::CTypeTransform(float v)
{
	sprintf(this->buf,"%f",v);
}

CTypeTransform::CTypeTransform(double v)
{
	sprintf(this->buf,"%0.0f",v);
}
CTypeTransform::CTypeTransform(unsigned int v)
{
	sprintf(this->buf,"%d",v);
}
CTypeTransform::CTypeTransform(short v)
{
	sprintf(this->buf,"%d",v);
}
CTypeTransform::CTypeTransform(bool v)
{
	if(true == v)
	{
		strcpy(buf,"true");
	}
	else
	{
		strcpy(buf,"false");
	}
}
CTypeTransform::CTypeTransform(long64_t v)
{
#ifdef CDE_WIN32
	sprintf(this->buf,"%I64d",v);
#else
	sprintf(this->buf,"%lld",v);
#endif
}
CTypeTransform::~CTypeTransform()
{

}

std::string CTypeTransform::toString()
{
	return this->buf;
}
