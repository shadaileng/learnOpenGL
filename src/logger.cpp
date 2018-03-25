#include "logger.h"
#include <ctime>

std::ofstream Logger::info_log_stream;					//信息日志输出流
std::ofstream Logger::warn_log_stream;					//警告日志输出流
std::ofstream Logger::erro_log_stream;					//错误日志输出流

void initLogger(const std::string& info_log_filename, const std::string& warn_log_filename, const std::string& erro_log_filename){
	Logger::info_log_stream.open(info_log_filename.c_str());
	Logger::warn_log_stream.open(warn_log_filename.c_str());
	Logger::erro_log_stream.open(erro_log_filename.c_str());
}

std::ostream& Logger::getStream(log_rank_t log_rank){
	#ifdef Terminate
	return (INFO == log_rank ? std::cout : std::cerr);
	#else
	return (INFO == log_rank ? (Logger::info_log_stream.is_open() ? info_log_stream : std::cout) : (WARNING == log_rank ? (Logger::warn_log_stream.is_open() ? warn_log_stream : std::cerr) : (Logger::erro_log_stream.is_open() ? erro_log_stream : std::cerr)));
	#endif
}

std::ostream& Logger::start(log_rank_t log_rank, const std::string& filename, const int line, const std::string& func){
	time_t tm;
	time(&tm);
	struct tm* currentTime = localtime(&tm);
	char time_str[128] = {0};
	sprintf(time_str, "%04d-%02d-%02d %02d:%02d:%02d", currentTime->tm_year + 1900, currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);
	
	std::string flag = INFO == log_rank ? "INFO" : (WARNING == log_rank ? "WARNING" : "ERROR");
	std::stringstream buf;
	buf << "[" << flag << "]" << time_str << " file:" << filename << " function: " << func << " line: " << line << " >>> " <<std::flush;
	
	return getStream(log_rank) << buf.str();
}

Logger::~Logger(){
	getStream(log_rank_level)<<std::endl<<std::flush;
	
	if(FATAL == log_rank_level){
		info_log_stream.close();
		warn_log_stream.close();
		erro_log_stream.close();
		std::cout<<"FATAL"<<std::endl;
		abort();
	}
}
