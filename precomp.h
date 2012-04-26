/*
   +----------------------------------------------------------------------------------------------+
   | Windows Cache for PHP                                                                        |
   +----------------------------------------------------------------------------------------------+
   | Copyright (c) 2009, Microsoft Corporation. All rights reserved.                              |
   |                                                                                              |
   | Redistribution and use in source and binary forms, with or without modification, are         |
   | permitted provided that the following conditions are met:                                    |
   | - Redistributions of source code must retain the above copyright notice, this list of        |
   | conditions and the following disclaimer.                                                     |
   | - Redistributions in binary form must reproduce the above copyright notice, this list of     |
   | conditions and the following disclaimer in the documentation and/or other materials provided |
   | with the distribution.                                                                       |
   | - Neither the name of the Microsoft Corporation nor the names of its contributors may be     |
   | used to endorse or promote products derived from this software without specific prior written|
   | permission.                                                                                  |
   |                                                                                              |
   | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS  |
   | OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF              |
   | MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE   |
   | COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,    |
   | EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE|
   | GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED   |
   | AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING    |
   | NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED |
   | OF THE POSSIBILITY OF SUCH DAMAGE.                                                           |
   +----------------------------------------------------------------------------------------------+
   | Module: precomp.h                                                                            |
   +----------------------------------------------------------------------------------------------+
   | Author: Kanwaljeet Singla <ksingla@microsoft.com>                                            |
   +----------------------------------------------------------------------------------------------+
*/

#ifndef _PRECOMP_H_
#define _PRECOMP_H_

#define PHP_WINCACHE_EXTNAME   "wincache"
#define PHP_WINCACHE_EXTVER    "1.3.0.0"

/* comment following line for release builds */
/* #define WINCACHE_DEBUG */

#ifdef PHP_WIN32
 #define PHP_WINCACHE_API __declspec(dllexport)
#else
 #define PHP_WINCACHE_API
#endif

#ifdef HAVE_CONFIG_H
 #include "config.h"
#endif

#ifdef ZTS
 #include "TSRM.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "sapi.h"
#include "ext/standard/info.h"
#include "ext/standard/php_smart_str.h"
#include "ext/session/php_session.h"
#include "zend_extensions.h"
#include "php_open_temporary_file.h"

#include <tlhelp32.h>

#define ALIGNDWORD(size)   (((size) % 4) ? ((size)+(4-((size) % 4))) : (size))
#define ALIGNQWORD(size)   (((size) % 8) ? ((size)+(8-((size) % 8))) : (size))

#if PHP_VERSION_ID >= 60000
 #define PHP_VERSION_60
#elif PHP_VERSION_ID >= 50400
 #define PHP_VERSION_54
#elif PHP_VERSION_ID >= 50300
 #define PHP_VERSION_53
#elif PHP_VERSION_ID >= 50200
 #define PHP_VERSION_52
#endif

#if ZEND_MODULE_API_NO >= 20100409
#define ZEND_ENGINE_2_4
#endif
#if ZEND_MODULE_API_NO > 20060613
#define ZEND_ENGINE_2_3
#endif
#if ZEND_MODULE_API_NO > 20050922
#define ZEND_ENGINE_2_2
#endif
#if ZEND_MODULE_API_NO > 20050921
#define ZEND_ENGINE_2_1
#endif

#ifdef _ASSERT
 #undef _ASSERT
#endif

#ifdef WINCACHE_DEBUG
# define WINCACHE_TEST
# define _ASSERT(x)   if(!(x)) { dprintalways(#x); if(IsDebuggerPresent()) { DebugBreak(); } }
#else
# define _ASSERT(x)
#endif

#if (defined(_MSC_VER) && (_MSC_VER < 1500))
# define IsDebuggerPresent() (0)
# define memcpy_s(dst, size, src, cnt) memcpy(dst, src, cnt)
# define sprintf_s(buffer, size, format) sprintf(buffer, format)
# define _snprintf_s wincache_php_snprintf_s
# define vsprintf_s(buffer, size, format, va_alist) vsprintf(buffer, format, va_alist)
# define strcpy_s(src, size, dst) strcpy(src, dst)
#endif

#define CACHE_TYPE_FILELIST        1
#define CACHE_TYPE_RESPATHS        2
#define CACHE_TYPE_FILECONTENT     3
#define CACHE_TYPE_BYTECODES       4
#define CACHE_TYPE_USERZVALS       5
#define CACHE_TYPE_SESSZVALS       6
#define CACHE_TYPE_FCNOTIFY        7

#define APLIST_TYPE_INVALID        255
#define APLIST_TYPE_GLOBAL         0
#define APLIST_TYPE_OPCODE_LOCAL   1

#define NUM_FILES_MINIMUM          1024
#define NUM_FILES_MAXIMUM          16384
#define OCACHE_SIZE_MINIMUM        15
#define OCACHE_SIZE_MAXIMUM        255
#define FCACHE_SIZE_MINIMUM        5
#define FCACHE_SIZE_MAXIMUM        255
#define ZCACHE_SIZE_MINIMUM        5
#define ZCACHE_SIZE_MAXIMUM        85
#define FILE_SIZE_MINIMUM          10
#define FILE_SIZE_MAXIMUM          4096
#define FCHECK_FREQ_MINIMUM        2
#define FCHECK_FREQ_MAXIMUM        300
#define TTL_VALUE_MINIMUM          60
#define TTL_VALUE_MAXIMUM          7200
#define INTERNED_SIZE_MINIMUM      4
#define INTERNED_SIZE_MAXIMUM      32

#include "wincache_error.h"
#include "wincache_debug.h"
#include "wincache_utils.h"
#include "wincache_lock.h"
#include "wincache_filemap.h"
#include "wincache_alloc.h"
#include "wincache_detours.h"
#include "wincache_ocache.h"
#include "wincache_opcopy.h"
#include "wincache_fcnotify.h"
#include "wincache_fcache.h"
#include "wincache_rplist.h"
#include "wincache_aplist.h"
#include "wincache_zvcache.h"
#include "wincache_session.h"
#include "wincache_string.h"
#include "php_wincache.h"

#endif /* _PRECOMP_H_ */
