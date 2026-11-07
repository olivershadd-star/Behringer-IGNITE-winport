#pragma once
#if defined(_WIN32) || defined(UNIX)
//#include "Common/Thirdparty/log_c/src/log.h"
//Disable logging temporarily
#define log_trace(...) while(0);
#define log_debug(...) while(0);
#define log_info(...)  while(0);
#define log_warn(...)  while(0);
#define log_error(...) while(0);
#define log_fatal(...) while(0);
#else
//Disable logging for other platforms
#define log_trace(...) while(0);
#define log_debug(...) while(0);
#define log_info(...)  while(0);
#define log_warn(...)  while(0);
#define log_error(...) while(0);
#define log_fatal(...) while(0);
#endif
