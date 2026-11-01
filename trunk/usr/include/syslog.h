#ifndef _SYSLOG_H_
#define _SYSLOG_H_
/* stub */
void syslog(int, const char *, ...);
#endif

#define LOG_MASK(pri)     (1 << (pri))
#define LOG_PRI(mask)     ((mask) & 7)
#define LOG_NDELAY        0x08
#define LOG_FACMASK       0x03
#define _PATH_LOG "/dev/log"

#define LOG_PRIMASK 0x07
#define LOG_ERR     3
#define LOG_CONS    0x02
#define LOG_PERROR  0x20
#define LOG_PID     0x01

void vsyslog(int pri, const char *fmt, __builtin_va_list ap);
void openlog(const char *ident, int logstat, int logfac);

/* facility codes */
#define LOG_USER    0
#define LOG_MAIL    1
#define LOG_DAEMON  3
#define LOG_AUTH    4
#define LOG_SYSLOG  5
#define LOG_LPR     6
#define LOG_NEWS    7
#define LOG_UUCP    8
#define LOG_CRON    9
#define LOG_LOCAL0  16
#define LOG_LOCAL1  17
#define LOG_LOCAL2  18
#define LOG_LOCAL3  19
#define LOG_LOCAL4  20
#define LOG_LOCAL5  21
#define LOG_LOCAL6  22
#define LOG_LOCAL7  23
