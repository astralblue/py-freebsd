/*
 * statfs.c
 *
 * statfs, fstatfs, getfsstat bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 06:15:55 $
 * Created : 14 June 2002
 *
 * $Revision: 1.4 $
 */


/*
 * Constants Listing
 */
#if defined(PYFB_CONSTANTS)

CONST_INT (MNT_RDONLY)
CONST_INT (MNT_NOEXEC)
CONST_INT (MNT_NOSUID)
CONST_INT (MNT_NODEV)
CONST_INT (MNT_SYNCHRONOUS)
CONST_INT (MNT_ASYNC)
CONST_INT (MNT_LOCAL)
CONST_INT (MNT_QUOTA)
CONST_INT (MNT_ROOTFS)
CONST_INT (MNT_EXRDONLY)
CONST_INT (MNT_EXPORTED)
CONST_INT (MNT_DEFEXPORTED)
CONST_INT (MNT_EXPORTANON)
CONST_INT (MNT_EXKERB)
CONST_INT (MNT_WAIT)
CONST_INT (MNT_NOWAIT)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (statfs)
METHOD (fstatfs)
METHOD (getfsstat)


/*
 * Function Bindings
 */
#else

#include <sys/mount.h>

static PyObject *
PyObject_FromStatfs(struct statfs *buf)
{
    PyObject *r, *fsid;

    r = PyDict_New();
    fsid = PyTuple_New(2);

    SETDICT_INT(r, "bsize",     buf->f_bsize);
    SETDICT_INT(r, "iosize",    buf->f_iosize);
    SETDICT_INT(r, "blocks",    buf->f_blocks);
    SETDICT_INT(r, "bfree",     buf->f_bfree);
    SETDICT_INT(r, "bavail",    buf->f_bavail);
    SETDICT_INT(r, "files",     buf->f_files);
    SETDICT_INT(r, "ffree",     buf->f_ffree);
    PyTuple_SET_ITEM(fsid, 0, PyInt_FromLong((long)buf->f_fsid.val[0]));
    PyTuple_SET_ITEM(fsid, 1, PyInt_FromLong((long)buf->f_fsid.val[1]));
    PyDict_SetItemString(r, "fsid", fsid);
    Py_DECREF(fsid);
    SETDICT_INT(r, "owner",     buf->f_owner);
    SETDICT_INT(r, "type",      buf->f_type);
    SETDICT_INT(r, "flags",     buf->f_flags);
    SETDICT_INT(r, "syncwrites",    buf->f_syncwrites);
    SETDICT_INT(r, "asyncwrites",   buf->f_asyncwrites);
    SETDICT_STR(r, "fstypename",    buf->f_fstypename);
    SETDICT_STR(r, "mntonname",     buf->f_mntonname);
    SETDICT_INT(r, "syncreads",     buf->f_syncreads);
    SETDICT_INT(r, "asyncreads",    buf->f_asyncreads);
    SETDICT_STR(r, "mntfromname",   buf->f_mntfromname);

    return r;
}


static char Py_statfs__doc__[] =
"statfs(path): get file system statistics";

static PyObject *
Py_statfs(PyObject *self, PyObject *args)
{
    struct statfs buf;
    char *path;

    if (! PyArg_ParseTuple(args, "s:statfs", &path))
        return NULL;

    if (statfs(path, &buf) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    return PyObject_FromStatfs(&buf);
}


static char Py_fstatfs__doc__[] =
"fstatfs(fd): get file system statistics";

static PyObject *
Py_fstatfs(PyObject *self, PyObject *args)
{
    struct statfs buf;
    int fd;

    if (! PyArg_ParseTuple(args, "i:fstatfs", &fd))
        return NULL;

    if (fstatfs(fd, &buf) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    return PyObject_FromStatfs(&buf);
}


static char Py_getfsstat__doc__[] =
"getfsstat(flags): get list of all mounted filesystems";

static PyObject *
Py_getfsstat(PyObject *self, PyObject *args)
{
    struct statfs *buf;
    int flags, nbufs, i;
    PyObject *r;

    if (! PyArg_ParseTuple(args, "i:getfsstat", &flags))
        return NULL;

    if ((nbufs = getfsstat(NULL, 0, flags)) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    } else if (nbufs == 0)
        return PyList_New(0);

    buf = PyMem_New(struct statfs, nbufs);

    if ((nbufs = getfsstat(buf, nbufs * sizeof(struct statfs), flags)) == -1) {
        PyMem_Del(buf);
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    r = PyList_New(nbufs);
    for (i = 0; i < nbufs; i++)
        PyList_SET_ITEM(r, i, PyObject_FromStatfs(&buf[i]));
    PyMem_Del(buf);

    return r;
}

#endif
