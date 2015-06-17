#include "mysqlmetadata.h"
#include "mysqlpublic.h"

#ifdef DAF_USED_MYSQL

using namespace DAFrame;
using namespace DAFrame::mysql;

CMetaData::CMetaData()
{
	memset(&_param,0,sizeof(_param));
}

CMetaData::~CMetaData()
{
	clear();
}

MYSQL_BIND* CMetaData::getMYSQL_BIND()
{
	return &_param;
}

void CMetaData::clear()
{
	if ( NULL != _param.buffer )
	{
		free(_param.buffer);
		_param.buffer = NULL;
	}
	if ( NULL != _param.length )
	{
		delete _param.length;
		_param.length = NULL;
	}
	if ( NULL != _param.is_null )
	{
		delete _param.is_null;
		_param.is_null = NULL;
	}
}

#endif