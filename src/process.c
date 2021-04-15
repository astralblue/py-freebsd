/*-
 * Copyright (c) 2002-2005 Hye-Shik Chang
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

#include "py2to3.h"

static char PyFB_getprogname__doc__[] =
"getprogname():\n"
"The getprogname() function returns the name of the program.  If the\n"
"name has not been set yet, it will return None.";

static PyObject *
PyFB_getprogname(PyObject *self)
{
	const char *progname;

	progname = getprogname();
	if (progname != NULL)
		return PyString_FromString(progname);
	Py_RETURN_NONE;
}


static char PyFB_setprogname__doc__[] =
"setprogname():\n"
"The setprogname() function sets the name of the program to be the\n"
"last component of the `progname` argument.";

static PyObject *
PyFB_setprogname(PyObject *self, PyObject *args)
{
	const char	*progname;
	static PyObject	*namestr = NULL;

	if (!PyArg_ParseTuple(args, "s:setprogname", &progname))
		return NULL;
	/*
	 * Setprogname(3) does not copy the string, it only stores the
	 * string pointer. Make sure that the string object does not
	 * get garbage collected and its memory reused!
	 */
	Py_XDECREF(namestr);	/* maybe free old progname */
	PyArg_ParseTuple(args, "O", &namestr);
	Py_INCREF(namestr);	/* keep new progname object */

	setprogname(progname);
	Py_RETURN_NONE;
}


static char PyFB_setproctitle__doc__[] =
"setproctitle(title):\n"
"The setproctitle() library routine sets the process title that\n"
"appears on the ps(1) command. The progname and a colon are\n"
"prepended automatically. This behaviour is suppressed when the\n"
"title starts with a dash (-) character. Calling with a None\n"
"argument restores a default process title.";

static PyObject *
PyFB_setproctitle(PyObject *self, PyObject *args)
{
	const char *newtitle;

	if (!PyArg_ParseTuple(args, "z:setproctitle", &newtitle))
		return NULL;

	if (newtitle == NULL)
		setproctitle(NULL);
	else if (*newtitle == '-')
		setproctitle("-%s", newtitle+1);
	else
		setproctitle("%s", newtitle);
	Py_RETURN_NONE;
}
