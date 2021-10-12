/*******************************************************************************
 * PES Assignment 4
 * File Name: log.h
 * Author: Howdy Pierce
 *********************************************************************************/

/*
 * log.h - abstraction away from printf
 */

#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include "fsl_debug_console.h"

#ifdef DEBUG
#  define LOG PRINTF
#else
#  define LOG(...)
#endif

#endif /* LOG_H_ */
