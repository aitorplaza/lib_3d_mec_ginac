#ifdef TIME_ON
  #include <sys/time.h>		/* struct timeval */
  #include <unistd.h>			/* gettimeofday() */

  static double timestamp()
  {
	  struct timeval tp;
	  if (0 != gettimeofday(&tp, NULL)) {return 0.0;}
	  return ((double) tp.tv_sec) + ((double) tp.tv_usec) / 1000000.0;
  }
#endif
