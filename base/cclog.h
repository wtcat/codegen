#ifndef BASE_CCLOG_H_
#define BASE_CCLOG_H_

#ifdef __cplusplus
#include "spdlog/spdlog.h"

#define cclog_info(_logger, ...)  spdlog::get(#_logger)->info(__VA_ARGS__)
#define cclog_warn(_logger, ...)  spdlog::get(#_logger)->warn(__VA_ARGS__)
#define cclog_err(_logger, ...)   spdlog::get(#_logger)->error(__VA_ARGS__)

#else

#define cclog_info(_logger, ...)  
#define cclog_warn(_logger, ...)  
#define cclog_err(_logger, ...)   

#endif /* __cplusplus */

#endif /* BASE_CCLOG_H_ */