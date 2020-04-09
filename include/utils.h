#ifndef CS4417_PROJECT_DEMO_UTILS_H
#define CS4417_PROJECT_DEMO_UTILS_H

#include <sys/types.h>

ssize_t recoverable_read(int fd, void *buf, size_t len);
ssize_t recoverable_write(int fd, const void *buf, size_t len);

#endif //CS4417_PROJECT_DEMO_UTILS_H
