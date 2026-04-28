#include <unistd.h>

constexpr int RIO_BUFSIZE = 8192;

typedef struct
{
    int rio_fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
} rio_t;

extern ssize_t rio_readn(int fd, void *usrbuf, size_t n);

extern ssize_t rio_writen(int fd, void *usrbuf, size_t n);

extern void rio_readinitb(rio_t *rp, int fd);

extern ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);

extern ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

extern ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
