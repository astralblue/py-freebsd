/*
 * fstab.c
 *
 * fstab bindings
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

METHOD_NOARGS (getfsent)
METHOD (getfsspec)
METHOD (getfsfile)


/*
 * Function Bindings
 */
#else

#include <fstab.h>


static PyObject *
PyObject_FromFstab(struct fstab *tab)
{
    PyObject *r;

    r = PyDict_New();
    SETDICT_STR(r, "spec", tab->fs_spec);
    SETDICT_STR(r, "file", tab->fs_file);
    SETDICT_STR(r, "vfstype", tab->fs_vfstype);
    SETDICT_STR(r, "mntops", tab->fs_mntops);
    SETDICT_STR(r, "type", tab->fs_type);
    SETDICT_INT(r, "freq", tab->fs_freq);
    SETDICT_INT(r, "passno", tab->fs_passno);

    return r;
}


static char Py_getfsent__doc__[] =
"getfsent(): get whole file system descriptor file entry";

static PyObject *
Py_getfsent(PyObject *self)
{
    struct fstab *tab;
    PyObject *r, *m;

    if (setfsent() == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    r = PyList_New(0);
    while ((tab = getfsent())) {
        m = PyObject_FromFstab(tab);
        PyList_Append(r, m);
        Py_DECREF(m);
    }
    endfsent();

    return r;
}


static char Py_getfsspec__doc__[] =
"getfsspec(spec): get file system descriptor file entry by spec";

static PyObject *
Py_getfsspec(PyObject *self, PyObject *args)
{
    struct fstab *tab;
    char *spec;

    if (! PyArg_ParseTuple(args, "s:getfsspec", &spec))
        return NULL;

    if ((tab = getfsspec(spec)) == NULL) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    return PyObject_FromFstab(tab);
}


static char Py_getfsfile__doc__[] =
"getfsfile(file): get file system descriptor file entry by file";

static PyObject *
Py_getfsfile(PyObject *self, PyObject *args)
{
    struct fstab *tab;
    char *file;

    if (! PyArg_ParseTuple(args, "s:getfsfile", &file))
        return NULL;

    if ((tab = getfsfile(file)) == NULL) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    return PyObject_FromFstab(tab);
}

#endif
