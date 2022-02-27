#include "server.h"

/* Get the real time */
char* get_time (void)
{
  time_t rawtime;
  struct tm * timeinfo;

  time(&rawtime);
  timeinfo = localtime(&rawtime);
  return (asctime(timeinfo));
}
