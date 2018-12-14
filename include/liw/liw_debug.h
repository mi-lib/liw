/* LIW - Linux Wizard
 * Copyright (C) 2000 Tomomichi Sugihara (Zhidao)
 */
/*! \file liw_debug.h
 * \brief miscellanies for debugging.
 * \author Zhidao
 */

#ifndef __LIW_DEBUG_H__
#define __LIW_DEBUG_H__

#include <liw/liw_time.h>

__BEGIN_DECLS

/* assertion */

#define liwAssert(msg,op) do{\
  if( op == -1 ){\
    perror( msg );\
    ZRUNERROR( "operation failed" );\
    fflush( stderr );\
    exit( errno );\
  }\
} while(0)

/* execution time majorment */

#define MEASURE_EXEC_CLOCK( clk, expr ) do{\
  struct timeval __z_tv1, __z_tv2;\
\
  gettimeofday( &__z_tv1, NULL );\
  expr;\
  gettimeofday( &__z_tv2, NULL );\
  *(clk) = tv_usec(&__z_tv2) - tv_usec(&__z_tv1);\
} while(0)

#define CLOCK2SEC( clk ) ( (double)clk / CLOCKS_PER_SEC )

#define MEASURE_EXEC_SEC( clk, expr ) do{\
  long __z_clk;\
  MEASURE_EXEC_CLOCK( &__z_clk, expr );\
  *(clk) = CLOCK2SEC( __z_clk );\
} while(0)

__END_DECLS

#endif /* __LIW_DEBUG_H__ */
