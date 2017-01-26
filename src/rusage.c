/*
 * rusage.c
 *
 * getrusage binding
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

CONST_INT (RUSAGE_SELF)
CONST_INT (RUSAGE_CHILDREN)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (getrusage)


/*
 * Function Bindings
 */
#else


static char Py_getrusage__doc__[] =
"getrusage(who): get information about resource utilization";

static PyObject *
Py_getrusage(PyObject *self, PyObject *args)
{
    struct rusage rup;
    PyObject *r;
    int who;

    if (! PyArg_ParseTuple(args, "i:getrusage", &who))
        return NULL;

    if (getrusage(who, &rup) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    r = PyDict_New();

    SETDICT_DOUBLE(r, "utime",
            ((double)rup.ru_utime.tv_sec) + ((double)rup.ru_utime.tv_usec / 1000000.0));
    SETDICT_DOUBLE(r, "stime",
            ((double)rup.ru_stime.tv_sec) + ((double)rup.ru_stime.tv_usec / 1000000.0));
    SETDICT_INT(r, "maxrss",   rup.ru_maxrss);
    SETDICT_INT(r, "ixrss",    rup.ru_ixrss);
    SETDICT_INT(r, "idrss",    rup.ru_idrss);
    SETDICT_INT(r, "isrss",    rup.ru_isrss);
    SETDICT_INT(r, "minflt",   rup.ru_minflt);
    SETDICT_INT(r, "majflt",   rup.ru_majflt);
    SETDICT_INT(r, "nswap",    rup.ru_nswap);
    SETDICT_INT(r, "inblock",  rup.ru_inblock);
    SETDICT_INT(r, "oublock",  rup.ru_oublock);
    SETDICT_INT(r, "msgsnd",   rup.ru_msgsnd);
    SETDICT_INT(r, "msgrcv",   rup.ru_msgrcv);
    SETDICT_INT(r, "nsignals", rup.ru_nsignals);
    SETDICT_INT(r, "nvcsw",    rup.ru_nvcsw);
    SETDICT_INT(r, "nivcsw",   rup.ru_nivcsw);

    return r;
}

#endif
