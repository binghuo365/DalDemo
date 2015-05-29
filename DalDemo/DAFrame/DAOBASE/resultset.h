#ifndef _CDF_RESULTSET_H_
#define _CDF_RESULTSET_H_

#include "framework/cdf_common.h"
#include "framework/util/datetime.h"
namespace cdf
{
class CResultSet
{
  public:
	virtual ~CResultSet(){};

    virtual void close() = 0 ;

    virtual int getColumnCount() = 0 ;

	virtual std::string getColumnName(int index ) = 0 ;

	virtual EDATATYPE getColumnDataType(int index ) = 0 ;

	virtual int getStringMaxSize( int index ){ return 0; } ;

    virtual bool next()=0;

    virtual int findColumn(const char* columnName) = 0 ;

    virtual char getByte(
		int  index ,
		bool nullThrow = true , 
		char defaultValue = 0 ) = 0 ;

    virtual char getByte( 
		const char* columnName,
		bool nullThrow = true,
		char defaultValue = 0) = 0 ;

    virtual bool getBytes(
		int index, 
		char* outBuffer, 
		int& length ,
		bool nullThrow = true ,
		const char* defaultValue = "" ) = 0;

    virtual bool getBytes(
		const char* columnName, 
		char* outBuffer , 
		int& length , 
		bool nullThrow = true,
		const char* defaultValue = ""
		)=0;

    virtual bool getBoolean(
		int index ,
		bool nullThrow = true ,
		bool defaultValue = false 
		)=0;

    virtual bool getBoolean(
		const char* column ,
		bool nullThrow = true ,
		bool defaultValue = false 
		)=0;

    virtual std::string getString(
		int index ,
		bool nullThrow = true ,
		const char* defaultValue = ""
		)=0;

    virtual std::string getString(
		const char* pColumn , 
		bool bNulLThrow = true , 
		const char* defaultValue = "" 
		)=0;

    virtual int getInt( 
		int index , 
		bool nullThrow = true , 
		int defaultValue = 0 
		)=0;

    virtual int getInt( 
		const char* column , 
		bool nullThrow = true , 
		int defaultValue= 0 ) = 0 ;

    virtual double getDouble(
		int index , 
		bool nullThrow = true , 
		double defaultValue = 0 
		) = 0 ;

    virtual double getDouble( const char* column , 
		bool nullThrow = true , 
		double defaultValue = 0 
		) = 0 ;

    virtual bool isNull( int index ) = 0 ;

    virtual bool isNull( const char* column ) = 0 ;

    virtual CDateTime getDate( 
		int index , 
		bool nullThrow = true , 
		const CDateTime& defaultValue = CDateTime::getThreadDt()
		) = 0 ;

    virtual CDateTime getDate(
		const char* column ,
		bool nullThrow = true ,
		const CDateTime& defaultValue = CDateTime::getThreadDt()
		) = 0 ;

    virtual CDateTime getTime(
		int index , 
		bool nullThrow = true , 
		const CDateTime& defaultValue = CDateTime::getThreadDt() 
		) = 0 ;

    virtual CDateTime getTime( 
		const char* column , 
		bool nullThrow = true , 
		const CDateTime& defaultValue = CDateTime::getThreadDt()
		) = 0 ;

    virtual CDateTime getTimestamp(
		int index , 
		bool nullThrow = true , 
		const CDateTime& defaultValue = CDateTime::getThreadDt()
		) = 0 ;

    virtual CDateTime getTimestamp(
		const char* column , 
		bool nullThrow = true , 
		const CDateTime& defaultValue = CDateTime::getThreadDt()
		) = 0 ;

    virtual long64_t getLong64(
		int index , 
		bool nullThrow = true , 
		long64_t defaultValue = 0
		) = 0 ;

    virtual long64_t getLong64( 
		const char* column , 
		bool nullThrow = true , 
		long64_t defaultValue = 0 
		)=0;

	virtual bool init() = 0;

};

}


#endif /* CRESULTSET_H_HEADER_INCLUDED_BB3264A8 */
