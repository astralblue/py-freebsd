/*
 * login.c
 *
 * getlogin, setlogin bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 10:34:30 $
 * Created : 13 June 2002
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

METHOD (getlogin)
METHOD (setlogin)


/*
 * Function Bindings
 */
#else


static char Py_getlogin__doc__[] =
"getlogin(): get login name";

static PyObject *
Py_getlogin(PyObject *self)
{
    char logname[MAXLOGNAME+1];

    if (getlogin_r(logname, MAXLOGNAME+1) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    return PyString_FromString(logname);
}

static char Py_setlogin__doc__[] =
"setlogin(): set login name";

static PyObject *
Py_setlogin(PyObject *self, PyObject *args)
{
    char *logname;

    if (! PyArg_ParseTuple(args, "s:setlogin", &logname))
        return NULL;

    if (setlogin(logname) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

#endif
