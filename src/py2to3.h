/*-
 * Copyright (c) 2018 Sippy Software, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef __PY2TO3_H
#define __PY2TO3_H

#if !defined(PY_MAJOR_VERSION)
    #error PY_MAJOR_VERSION is not defined
#endif

#if PY_MAJOR_VERSION >= 3
    #define PyInt_Check(OB) PyLong_Check(OB)
    #define PyInt_FromLong(V) PyLong_FromLong(V)
    #define PyInt_AsLong(OB) PyLong_AsLong(OB)
    #define PyString_FromStringAndSize(V, L) PyUnicode_DecodeASCII(V, L, NULL)
    #define PyString_FromString(V) PyUnicode_DecodeASCII(V, strlen(V), NULL)
    #define PyString_FromFormat(F, A...) PyUnicode_FromFormat(F, ## A)
    #define _PyString_Join(OB1, OB2) PyUnicode_Join(OB1, OB2)
    #define PyString_Check(OB) PyUnicode_Check(OB)
    #define PyString_GET_SIZE(OB) PyString_Size(OB)
    #define PyString_AS_STRING(OB) _PyString_AS_STRING(OB, alloca(1024), 1024)

static inline const char *
_PyString_AS_STRING(PyObject *us, char *sbuf, size_t blen)
{
    PyObject *as;

    as = PyUnicode_AsASCIIString(us);
    if (as == NULL)
        return (NULL);
    strncpy(sbuf, PyBytes_AsString(as), blen);
    Py_DECREF(as);
    return (sbuf);
}

static inline ssize_t
PyString_Size(PyObject *us)
{
    PyObject *as;
    ssize_t rval;

    as = PyUnicode_AsASCIIString(us);
    if (as == NULL)
        return (-1);
    rval = strlen(PyBytes_AsString(as));
    Py_DECREF(as);
    return (rval);
}
#else
    #define PyBytes_FromStringAndSize(V, L) PyString_FromStringAndSize(V, L)
#endif

#endif /* __PY2TO3_H */
