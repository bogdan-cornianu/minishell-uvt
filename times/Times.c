

#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

/* Note: return value overflows */

int times(struct tms *buf)
{
        return -1;
}


long _times (struct tms *buffer)
{
  struct timeval tv;

  buffer->tms_utime = clock ();  /* clock () * HZ / CLOCKS_PER_SEC */
  buffer->tms_stime = 0;
  buffer->tms_cutime = 0;
  buffer->tms_cstime = 0;
  if (_gettimeofday (&tv, NULL) != 0)
    return -1;
  return CLK_TCK * tv.tv_sec + (CLK_TCK * tv.tv_usec) / 1000000;
}

