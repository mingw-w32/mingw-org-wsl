/*
 * alloca.h
 *
 * Declarations for the alloca() function API, conforming to both GNU and
 * Microsoft's implementation conventions.
 *
 *
 * $Id$
 *
 * Written by Keith Marshall <keith@users.osdn.me>
 * Copyright (C) 2018, MinGW.org Project.
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#ifndef _ALLOCA_H
#define _ALLOCA_H
/* Microsoft requires the alloca() API to be declared in <malloc.h>;
 * GNU declares it in <alloca.h>, with default inclusion by <stdlib.h>
 * when !__STRICT_ANSI__.  To achieve compatibility with both, we will
 * define it in the GNU manner, conditionally including this file when
 * reading <stdlib.h>, and UNCONDITIONALLY including it in <malloc.h>
 */
#ifdef __GNUC__
#pragma GCC system_header
/* This implementation is unsupported, for any compiler other than GCC,
 * (which is the standard MinGW compiler, in any case); all MinGW source
 * may assume that <_mingw.h> has been included, so ensure that it is.
 */
#include <_mingw.h>

/* We must also ensure that the "size_t" type definition is in scope;
 * we may guarantee this, by selective inclusion from <stddef.h>
 */
#define __need_size_t
#include <stddef.h>

_BEGIN_C_DECLS

#if defined _GNU_SOURCE || ! defined _NO_OLDNAMES
/* This is the GNU standard API; it is also compatible with Microsoft's
 * original, but now deprecated, naming convention.
 */
__CRT_ALIAS void *alloca( size_t __n ){ return __builtin_alloca( __n ); }
#endif	/* _GNU_SOURCE || !_NO_OLDNAMES */

/* This represents the same API, but conforms to Microsoft's currently
 * preferred naming convention.
 */
__CRT_ALIAS void *_alloca( size_t __n ){ return __builtin_alloca( __n ); }

_END_C_DECLS

#endif	/* __GNUC__ */
#endif	/* !_ALLOCA_H: $RCSfile$: end of file */
