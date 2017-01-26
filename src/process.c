/*
 * process.c
 *
 * various process bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 10:34:30 $
 * Created : 14 June 2002
 *
 * $Revision: 1.3 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD_NOARGS (getprogname)
METHOD (setprogname)
METHOD (setproctitle)


/*
 * Function Bindings
 */
#else

static char Py_getprogname__doc__[] =
"getprogname(): get the program name";

static PyObject *
Py_getprogname(PyObject *self)
{
    const char *progname;

    progname = getprogname();
    if (progname == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    } else
        return PyString_FromString(progname);
}


static char Py_setprogname__doc__[] =
"setprogname(): set the program name";

static PyObject *
Py_setprogname(PyObject *self, PyObject *args)
{
    char *progname;

    if (! PyArg_ParseTuple(args, "s:setprogname", &progname))
        return NULL;

    setprogname(progname);

    Py_INCREF(Py_None);
    return Py_None;
}


static char Py_setproctitle__doc__[] =
"setproctitle(title): set the process title for ps(1)";

static PyObject *
Py_setproctitle(PyObject *self, PyObject *args)
{
    char *newtitle;

    if (! PyArg_ParseTuple(args, "s:setproctitle", &newtitle))
        return NULL;

    setproctitle(newtitle);

    Py_INCREF(Py_None);
    return Py_None;
}

#endif
