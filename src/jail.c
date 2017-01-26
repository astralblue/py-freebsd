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

#include <sys/param.h>
#include <sys/jail.h>

static char PyFB_jail__doc__[] =
"jail(path, hostname, ip_number):\n"
"The jail() system call sets up a jail and locks the current process\n"
"in it.  The ``path'' should be set to the directory which is to be\n"
"the root of the prison.  The ``hostname'' can be set to the hostname\n"
"of the prison.  This can be changed from the inside of the prison.\n"
"The ``ip_number'' can be set to the IP number assigned to the prison.";

static PyObject *
PyFB_jail(PyObject *self, PyObject *args)
{
#if __FreeBSD_version >= 800056 || \
    (__FreeBSD_version < 800000 && __FreeBSD_version >= 701103)
	struct jail jp;
	struct in_addr ia;
	char *ipaddr;
	int error;

	if (!PyArg_ParseTuple(args, "sss:jail", &(jp.path),
			      &(jp.hostname), &ipaddr))
		return NULL;

	ia.s_addr	= inet_addr(ipaddr);
	if (ia.s_addr == INADDR_NONE) {
		PyErr_SetString(PyExc_ValueError, "malformed internet address");
		return NULL;
	}

	jp.version	= JAIL_API_VERSION;
	jp.jailname	= NULL;
	jp.ip4s		= 1;
	jp.ip4		= malloc(jp.ip4s * sizeof(struct in_addr));
	if (jp.ip4 == NULL) {
		PyErr_SetString(PyExc_ValueError, "Cannot allocate memory");
		return NULL;
	}
	jp.ip4->s_addr = ia.s_addr;
	jp.ip6s		= 0;
	jp.ip6		= NULL;

	error = jail(&jp);

	free(jp.ip4);

	if (error == -1)
		return OSERROR();

	Py_RETURN_NONE;
#else
	struct jail jp;
	char *ipaddr;

	if (!PyArg_ParseTuple(args, "sss:jail", &(jp.path),
			      &(jp.hostname), &ipaddr))
		return NULL;

	jp.version   = 0;
	jp.ip_number = inet_addr(ipaddr);

	if (jp.ip_number == INADDR_NONE) {
		PyErr_SetString(PyExc_ValueError, "malformed internet address");
		return NULL;
	}

	if (jail(&jp) == -1)
		return OSERROR();

	Py_RETURN_NONE;
#endif
}

#if __FreeBSD_version >= 500111

static char PyFB_jail_attach__doc__[] =
"jail_attach(jid):\n"
"Attach the current process to an existing jail, identified by jid.";

static PyObject *
PyFB_jail_attach(PyObject *self, PyObject *args)
{
	int jid;

	if (!PyArg_ParseTuple(args, "i:jail_attach", &jid))
		return NULL;

	if (jail_attach(jid) != 0)
		return OSERROR();

	Py_RETURN_NONE;
}

#endif /* __FreeBSD_version >= 500111 */

#if __FreeBSD_version >= 800084

static char PyFB_jail_remove__doc__[] =
"jail_remove(jid):\n"
"Remove the jail identified by jid.\n"
"\n"
"Kill all processes belonging to the jail, and remove any children of that jail.";

static PyObject *
PyFB_jail_remove(PyObject *self, PyObject *args)
{
	int jid;

	if (!PyArg_ParseTuple(args, "i:jail_remove", &jid))
		return NULL;

	if (jail_remove(jid) != 0)
		return OSERROR();

	Py_RETURN_NONE;
}

#endif /* __FreeBSD_version >= 800084 */
