/*
 * reboot.c
 *
 * reboot bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 09:27:44 $
 * Created : 14 June 2002
 *
 * $Revision: 1.4 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)

CONST_INT (RB_AUTOBOOT)
CONST_INT (RB_ASKNAME)
CONST_INT (RB_DFLTROOT)
CONST_INT (RB_DUMP)
CONST_INT (RB_HALT)
CONST_INT (RB_POWEROFF)
CONST_INT (RB_INITNAME)
CONST_INT (RB_KDB)
CONST_INT (RB_NOSYNC)
CONST_INT (RB_RDONLY)
CONST_INT (RB_SINGLE)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (reboot)


/*
 * Function Bindings
 */
#else

#include <sys/reboot.h>

static char Py_reboot__doc__[] =
"reboot([howto]): reboot system or halt processor";

static PyObject *
Py_reboot(PyObject *self, PyObject *args)
{
    int howto = RB_AUTOBOOT;

    if (! PyArg_ParseTuple(args, "|i:reboot", &howto))
        return NULL;

    if (reboot(howto) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

#endif
