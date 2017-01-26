/*
 * ktrace.c
 *
 * ktrace bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 06:15:54 $
 * Created : 14 June 2002
 *
 * $Revision: 1.3 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)

CONST_INT (KTROP_SET)
CONST_INT (KTROP_CLEAR)
CONST_INT (KTROP_CLEARFILE)
CONST_INT (KTRFLAG_DESCEND)
CONST_INT (KTRFAC_SYSCALL)
CONST_INT (KTRFAC_SYSRET)
CONST_INT (KTRFAC_NAMEI)
CONST_INT (KTRFAC_GENIO)
CONST_INT (KTRFAC_PSIG)
CONST_INT (KTRFAC_CSW)
CONST_INT (KTRFAC_INHERIT)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (ktrace)


/*
 * Function Bindings
 */
#else

#include <sys/ktrace.h>

static char Py_ktrace__doc__[] =
"ktrace(tracefile, ops, trpoints, pid): process tracing";

static PyObject *
Py_ktrace(PyObject *self, PyObject *args)
{
    char *tracefile;
    int ops, trpoints, pid;

    if (! PyArg_ParseTuple(args, "siii:ktrace", &tracefile, &ops, &trpoints, &pid))
        return NULL;

    if (ktrace(tracefile, ops, trpoints, pid) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

#endif
