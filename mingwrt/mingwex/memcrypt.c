/*
 * memcrypt.c
 *
 * Implementation of a cryptographically secure random data generator.
 * This provides a mechanism for filling a memory buffer, of specified
 * length, with cryptographically secure randomly generated bytes.
 *
 * $Id: memcrypt.c,v 5f021e118870 2020/07/20 19:17:27 keith $
 *
 * Written by Keith Marshall  <keith@users.osdn.me>
 * Copyright (C) 2013, 2014, 2018-2020, MinGW.org Project.
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, this permission notice, and the following
 * disclaimer shall be included in all copies or substantial portions of
 * the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OF OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */
#define WIN32_LEAN_AND_MEAN

#include <wincrypt.h>

#define CRYPTO_INLINE  static __inline__ __attribute__((__always_inline__))

CRYPTO_INLINE HCRYPTPROV crypto_provider( void )
#define RSA_MODE( OPT, FLAG )  PROV_RSA_##OPT, CRYPT_##FLAG
{
  /* Helper to establish a cryptographic provider context for the
   * cryptographically secure random number generator.
   *
   * At the outset, this provider requires initialization.
   */
  static HCRYPTPROV id = (HCRYPTPROV)(0);

  /* On second, and subsequent calls, it should already have been
   * initialized...
   */
  if( id != (HCRYPTPROV)(0) )
    /*
     * ...so, simply return the saved context handle...
     */
    return id;

  /* If we're still here, this must be the first call, (or any
   * preceding call failed to initialize the context); initialize
   * it now, and if successful...
   */
  if( CryptAcquireContext( &id, NULL, NULL, RSA_MODE( FULL, VERIFYCONTEXT ) ) )
    /*
     * ...return the now-initialized context handle.
     */
    return id;

  /* And finally, if we ever get to here, the context remains
   * uninitialized; ensure that it remains marked as such, and
   * return the uninitialized context handle.
   */
  return id = (HCRYPTPROV)(0);
}

void *__mingw_crypto_randomize( void *buf, size_t buflen )
{
  /* Helper to fill a specified buffer, of specified length,
   * with cryptographically secure random bytes...
   */
  if( CryptGenRandom( crypto_provider(), buflen, buf ) )
    /*
     * ...returning a pointer to the buffer, when successful...
     */
    return buf;

  /* ...or nothing, otherwise.
   */
  return NULL;
}

/* $RCSfile: memcrypt.c,v $: end of file */
