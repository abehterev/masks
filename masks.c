#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include <string.h>

#include <unistd.h>
#include <time.h>

#include "masks.h"

#ifdef DEBUG
#define DEBUG_TRACE(x) dbg_printf x

void dbg_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

#else
#define DEBUG_TRACE(x)
#endif

#define BYTETOBINARYPATTERN "%d%d%d%d %d%d%d%d% d%d%d%d% d%d%d%d"
#define BYTETOBINARY(byte)  \
  (byte & 0x8000 ? 1 : 0), \
  (byte & 0x4000 ? 1 : 0), \
  (byte & 0x2000 ? 1 : 0), \
  (byte & 0x1000 ? 1 : 0), \
  (byte & 0x0800 ? 1 : 0), \
  (byte & 0x0400 ? 1 : 0), \
  (byte & 0x0200 ? 1 : 0), \
  (byte & 0x0100 ? 1 : 0), \
  (byte & 0x0080 ? 1 : 0), \
  (byte & 0x0040 ? 1 : 0), \
  (byte & 0x0020 ? 1 : 0), \
  (byte & 0x0010 ? 1 : 0), \
  (byte & 0x0008 ? 1 : 0), \
  (byte & 0x0004 ? 1 : 0), \
  (byte & 0x0002 ? 1 : 0), \
  (byte & 0x0001 ? 1 : 0)


long count = 0;
uint16_t *flags;
uint32_t counters[16];

void init_arrays(){
  memset(counters,0,sizeof(counters));
  
  flags = malloc( count * sizeof(uint16_t) );
  DEBUG_TRACE(("DEBUG: Flags size [%d]\n", sizeof(uint16_t)));
}

void print_usage(void){
	fprintf(stderr,"Usage: masks -n <packet_num>\n\n"
	       );
	exit(EXIT_FAILURE);
}

void set_opt( int argc, char **argv){

	DEBUG_TRACE(("DEBUG: Options total [%d]\n", argc));
	
	if ( argc < 3 ) {
		print_usage();
		exit(EXIT_FAILURE);
	}
	
	int opt;
	
	while ((opt = getopt(argc, argv, "n:")) != -1) {
		switch (opt) {
			case 'n':
				DEBUG_TRACE(("DEBUG: Options [n] [%s]\n", optarg));
				count = atol(optarg);
				if ( count < 0 ){
				  fprintf(stderr, "ERR: Number less than zero!\n");
				  exit(EXIT_FAILURE);
				}
				break;
			default:
				print_usage();
		}
	}
}

void prepare_flags(){
  
	srandom ( time(NULL) + getpid() );
	
	long i;
	for (i = 0; i<count; i++){
		flags[i] = random();
	}
}

int main(int argc, char **argv){

	set_opt(argc, argv); // prepare parameters
	
	init_arrays(); // init counters and flags
	
	prepare_flags(); // randomize flags
	
	int n;
	
	for (n = 0; n < count; n++){
	  uint16_t flag = flags[n];
	    (flag & 0x8000 ? counters[0]++ : 0);
	    (flag & 0x4000 ? counters[1]++ : 0);
	    (flag & 0x2000 ? counters[2]++ : 0);
	    (flag & 0x1000 ? counters[3]++ : 0);
	    (flag & 0x0800 ? counters[4]++ : 0);
	    (flag & 0x0400 ? counters[5]++ : 0);
	    (flag & 0x0200 ? counters[6]++ : 0);
	    (flag & 0x0100 ? counters[7]++ : 0);
	    (flag & 0x0080 ? counters[8]++ : 0);
	    (flag & 0x0040 ? counters[9]++ : 0);
	    (flag & 0x0020 ? counters[10]++ : 0);
	    (flag & 0x0010 ? counters[11]++ : 0);
	    (flag & 0x0008 ? counters[12]++ : 0);
	    (flag & 0x0004 ? counters[13]++ : 0);
	    (flag & 0x0002 ? counters[14]++ : 0);
	    (flag & 0x0001 ? counters[15]++ : 0);
	    
	  DEBUG_TRACE(("DEBUG: FLAG[%d] = [%04X]\n", n, flag));
	}
	
    #ifdef DEBUG
	int i;
	for (i = 0; i < 16; i++){
	  DEBUG_TRACE(("DEBUG: Counter[%d] = [%d]\n", i, counters[i]));
	}
	
	for (i = 0; i < count; i++){
	  DEBUG_TRACE(("DEBUG: FLAGS[%d] = (%04X)\t"BYTETOBINARYPATTERN"\n", i, flags[i], BYTETOBINARY(flags[i])));
	}
	  DEBUG_TRACE(("\n"));
	  DEBUG_TRACE(("DEBUG: COUNT[1..16] =\t\t"));
	  
	  int j;
	  for (j=0; j<16; j++){
	    ( j!=0 && j%4 == 0 ) ? DEBUG_TRACE((" %d", counters[j])) : DEBUG_TRACE(("%d", counters[j]));
	  }
	  DEBUG_TRACE(("\n\n"));
    #endif
	int c;
	for (c=0; c<16; c++){
	  printf("Counter(%02d) = %08d\n", c+1, counters[c]);
	}
	free(flags);
	exit(EXIT_SUCCESS);
}