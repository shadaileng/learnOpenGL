/**
	logger.h
	created by 
		--Shdaileng
*/
#ifndef __LOGGER_H__
#define __LOGGER_H__
#define Terminate

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

typedef enum log_rank{
	INFO,
	WARNING,
	ERROR,
	FATAL
}log_rank_t;

// 日志初始化
// info_log_filename 信息日志文件名
// warn_log_filename 信息日志文件名
// erro_log_filename 信息日志文件名
void initLogger(const std::string& info_log_filename, const std::string& warn_log_filename, const std::string& erro_log_filename);

class Logger{
	friend void initLogger(const std::string& info_log_filename, const std::string& warn_log_filename, const std::string& erro_log_filename);
	
	public:
		Logger(log_rank_t log_rank): log_rank_level(log_rank){};
		~Logger();
	// 日志基本信息
	// log_rank 日志级别
	// line 	行号
	// func		函数
	static std::ostream& start(log_rank_t log_rank, const std::string& filename, const int line, const std::string& func);
	
	private:
		static std::ostream& getStream(log_rank_t log_rank);
		
		static std::ofstream info_log_stream;					//信息日志输出流
		static std::ofstream warn_log_stream;					//警告日志输出流
		static std::ofstream erro_log_stream;					//错误日志输出流
		
		log_rank_t log_rank_level;
};

#define LOG(log_rank) \
	Logger(log_rank).start(log_rank, __FILE__, __LINE__, __FUNCTION__)

#define CHECK(a)\
	if(!(a)){ \
		LOG(ERROR) << " Check failed " << endl << #a << " = " << (a); \
	} \
	
#define CHECK_NOT_NULL(a) \
	if(NULL == a){ \
		LOG(ERROR) << " Check not null failed " << endl << #a << " = " << (a); \
	} \

#define CHECK_NULL(a) \
	if(NULL != a){ \
		LOG(ERROR) << " Check null failed " << endl << #a << " != NULL"; \
	} \

#define CHECK_EQ(a, b) \
	if(a != b){ \
		LOG(ERROR) << " Check equal failed " << endl << #a << " = " << a << endl << #b << " = " << b; \
	} \

#define CHECK_NE(a, b) \
	if(a == b){ \
		LOG(ERROR) << " Check not equal failed " << endl << #a << " = " << a << endl << #b << " = " << b; \
	} \

#define CHECK_LT(a, b) \
	if(!(a < b)){ \
		LOG(ERROR) << " Check little than failed " << endl << #a << " = " << a << endl << #b << " = " << b; \
	} \

#define CHECK_GT(a, b) \
	if(!(a > b)){ \
		LOG(ERROR) << " Check great than failed " << endl << #a << " = " << a << endl << #b << " = " << b; \
	} \

#define CHECK_LE(a, b) \
	if((a > b)){ \
		LOG(ERROR) << " Check little equal failed " << endl << #a << " = " << a << endl << #b << " = " << b; \
	} \

#define CHECK_GE(a, b) \
	if((a < b)){ \
		LOG(ERROR) << " Check great equal failed " << endl << #a << " = " << a << endl << #b << " = " << b; \
	} \



#endif
