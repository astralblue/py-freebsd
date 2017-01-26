/*
 * sysctl.c
 *
 * sysctl related bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/27 04:56:02 $
 * Created : 14 June 2002
 *
 * $Revision: 1.5 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD_NOARGS (getloadavg)
METHOD_NOARGS (getosreldate)


/*
 * Function Bindings
 */
#else

#include <sys/sysctl.h>

static char Py_getloadavg__doc__[] =
"getloadavg(): get system load averages";

static PyObject *
Py_getloadavg(PyObject *self)
{
#define NSAMPLES 3
    double loadavg[NSAMPLES];
    int nsamples, i;
    PyObject *r;

    if ((nsamples = getloadavg(loadavg, NSAMPLES)) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return Py_None;
    }

    r = PyTuple_New(nsamples);
    for (i = 0; i < nsamples; i++)
        PyTuple_SET_ITEM(r, i, PyFloat_FromDouble(loadavg[i]));

    return r;
}


extern int getosreldate(void);

static char Py_getosreldate__doc__[] =
"getosreldate(): get OS's release date";

static PyObject *
Py_getosreldate(PyObject *self)
{
    int osreldate;

    if ((osreldate = getosreldate()) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return Py_None;
    }

    return PyInt_FromLong(osreldate);
}

#endif

/*
 * ex: ts=8 sts=4 et
 */
