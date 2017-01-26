/*
 * jail.c
 *
 * jail binding
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 09:27:44 $
 * Created : 13 June 2002
 *
 * $Revision: 1.4 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)



/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (jail)


/*
 * Function Bindings
 */
#else

#include <sys/jail.h>

static char Py_jail__doc__[] =
"jail(path, hostname, ipaddr): imprison current process and future decendants";

static PyObject *
Py_jail(PyObject *self, PyObject *args)
{
    struct jail jp;
    char *ipaddr;

    if (! PyArg_ParseTuple(args, "sss:jail", &(jp.path), &(jp.hostname), &ipaddr))
        return NULL;

    jp.version   = 0;
    jp.ip_number = inet_addr(ipaddr);

    if (jp.ip_number == INADDR_NONE) {
        PyErr_SetString(PyExc_ValueError, "malformed internet address");
        return NULL;
    }

    if (jail(&jp) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

#endif
