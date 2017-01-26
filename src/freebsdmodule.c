/*
 * freebsdmodule.c
 *
 * FreeBSD Platform Library - Python binding
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 10:34:30 $
 * Created : 12 June 2002
 *
 * $Revision: 1.15 $
 */

#include <iso646.h>
#include <sys/param.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <fcntl.h>

#include "Python.h"

#define __inline__ static inline

/*
 * Global Object & Utility Function and Macroes
 */

static PyObject *ErrorObject;

__inline__ void
PyDict_SetItemString_StealReference(PyObject *d, char *name, PyObject *o)
{
    PyDict_SetItemString(d, name, o);
    Py_DECREF(o);
}

#define SETDICT_INT(dict, name, value) \
            (PyDict_SetItemString_StealReference(dict, name, PyInt_FromLong((long) value)));
#define SETDICT_LONG(dict, name, value) \
            (PyDict_SetItemString_StealReference(dict, name, PyLong_FromLongLong((long long) value)));
#define SETDICT_DOUBLE(dict, name, value) \
            (PyDict_SetItemString_StealReference(dict, name, PyFloat_FromDouble((double) value)));
#define SETDICT_STR(dict, name, value) \
            PyDict_SetItemString_StealReference(dict, name, PyString_FromString(value));
#define SETDICT_CHAR(dict, name, value) \
            PyDict_SetItemString_StealReference(dict, name, PyString_FromFormat("%c", value));


/*
 * Code Area
 */

#include "modulecontents.h"


/*
 * Methods Declarations
 */

#define PYFB_METHODS
#define METHOD(name) {#name, (PyCFunction)Py_##name, METH_VARARGS, Py_##name##__doc__},
#define METHOD_KW(name) {#name, (PyCFunction)Py_##name, METH_VARARGS|METH_KEYWORDS, Py_##name##__doc__},
#define METHOD_NOARGS(name) {#name, (PyCFunction)Py_##name, METH_NOARGS, Py_##name##__doc__},

static struct PyMethodDef freebsd_methods[] = {
#include "modulecontents.h"
    {NULL, NULL},
};


/*
 * Module Initialization
 */

void
initfreebsd(void)
{
    PyObject *m, *d;

    m = Py_InitModule("freebsd", freebsd_methods);

    d = PyModule_GetDict(m);

#define PYFB_CONSTANTS
#define CONST_INT(value) SETDICT_INT(d, #value, value)
#define CONST_STR(value) SETDICT_STR(d, #value, value)
#define CONST_CHAR(value) SETDICT_CHAR(d, #value, value)

#include "version.h"
    CONST_STR (__version__)

#include "modulecontents.h"

    ErrorObject = PyErr_NewException("freebsd.error", NULL, NULL);
    PyDict_SetItemString(d, "error", ErrorObject);

    if (PyErr_Occurred())
         Py_FatalError("can't initialize the freebsd module");
}
