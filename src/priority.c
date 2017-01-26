/*
 * priority.c
 *
 * setpriority / getpriority binding
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/30 23:43:25 $
 * Created : 13 June 2002
 *
 * $Revision: 1.4 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)

CONST_INT (PRIO_PROCESS)
CONST_INT (PRIO_PGRP)
CONST_INT (PRIO_USER)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (getpriority)
METHOD (setpriority)


/*
 * Function Bindings
 */
#else

#include <sys/resource.h>

static char Py_getpriority__doc__[] =
"getpriority(which, who): get program scheduling priority";

static PyObject *
Py_getpriority(PyObject *self, PyObject *args)
{
    int which, who, r;

    if (!PyArg_ParseTuple(args,"ii:getpriority", &which, &who))
        return NULL;

    r = getpriority(which, who);
    if (errno == -1) { /* getpriority can return -1 legitimately */
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    } else
        return PyInt_FromLong((long) r);
}


static char Py_setpriority__doc__[] =
"setpriority(which, who, prio): set program scheduling priority";

static PyObject *
Py_setpriority(PyObject *self, PyObject *args)
{
    int which, who, prio, r;

    if (!PyArg_ParseTuple(args,"iii:setpriority", &which, &who, &prio))
        return NULL;

    if ((r = setpriority(which, who, prio)) != 0) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    } else {
        Py_INCREF(Py_None);
        return Py_None;
    }
}

#endif
