#ifndef __LOG_H__
#define __LOG_H__

#define MAX_LOG_LEVEL   256

#define BUF_SIZE        256
#define BUF_TIME_SIZE   32

// define log level
#define NONE    0
#define FATAL   1
#define ERROR   2
#define WARNING 3
#define INFO    4
#define DEBUG   5
#define TRACE   6

// TODO: log multi-threads safe

/**
 * Get the now time, format year-month-day hours:min:seconds,
 * for example, 2010-03-14 21:59:23.
 * The format time stores the buf_time.
 * @return: no return
 */
void get_now_time(char *buf_time);

/**
 * Write the message to the log file 
 * Log format,  [level][time][file | line | pid ][message].
 * For example, [INFO][2015-08-23 05:27:30][file: log.cpp | line: 50 | pid: 6359][log message]
 */
void write_to_log(int level, const char *file, int line, const char *message, ...);

#define LOG(level, args...)    write_to_log(level, __FILE__, __LINE__, args)

#endif 
