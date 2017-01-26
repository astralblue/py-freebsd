/*
 * rlimit.c
 *
 * getrlimit, setrlimit bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 06:15:55 $
 * Created : 13 June 2002
 *
 * $Revision: 1.4 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)

CONST_INT (RLIMIT_CORE)
CONST_INT (RLIMIT_CPU)
CONST_INT (RLIMIT_DATA)
CONST_INT (RLIMIT_FSIZE)
CONST_INT (RLIMIT_MEMLOCK)
CONST_INT (RLIMIT_NOFILE)
CONST_INT (RLIMIT_NPROC)
CONST_INT (RLIMIT_RSS)
CONST_INT (RLIMIT_STACK)
CONST_INT (RLIMIT_SBSIZE)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (getrlimit)
METHOD (setrlimit)


/*
 * Function Bindings
 */
#else


static char Py_getrlimit__doc__[] =
"getrlimit(resource): get maximum system resource consumption";

static PyObject *
Py_getrlimit(PyObject *self, PyObject *args)
{
    struct rlimit rlp;
    PyObject *r;
    int resource;

    if (! PyArg_ParseTuple(args, "i:getrlimit", &resource))
        return NULL;

    if (getrlimit(resource, &rlp) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    r = PyTuple_New(2);

    if (rlp.rlim_cur == RLIM_INFINITY) {
        Py_INCREF(Py_None);
        PyTuple_SET_ITEM(r, 0, Py_None);
    } else
        PyTuple_SET_ITEM(r, 0, PyLong_FromLongLong(rlp.rlim_cur));

    if (rlp.rlim_max == RLIM_INFINITY) {
        Py_INCREF(Py_None);
        PyTuple_SET_ITEM(r, 1, Py_None);
    } else
        PyTuple_SET_ITEM(r, 1, PyLong_FromLongLong(rlp.rlim_max));

    return r;
}


static char Py_setrlimit__doc__[] =
"setrlimit(resource, rlim_cur, rlim_max): set maximum system resource consumption";

static PyObject *
Py_setrlimit(PyObject *self, PyObject *args)
{
    struct rlimit rlp;
    int resource;

    if (! PyArg_ParseTuple(args, "iLL:setrlimit", &resource, &(rlp.rlim_cur), &(rlp.rlim_max)))
        return NULL;

    if (setrlimit(resource, &rlp) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

#endif
