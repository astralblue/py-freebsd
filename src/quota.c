/*
 * quota.c
 *
 * quota functions binding
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

CONST_INT (USRQUOTA)
CONST_INT (GRPQUOTA)


/*
 * Methods Listing
 */
#elif defined(PYFB_METHODS)

METHOD (quotaon)
METHOD (quotaoff)
METHOD (getquota)
METHOD_KW (setquota)
METHOD (quotasync)


/*
 * Function Bindings
 */
#else

#include <ufs/ufs/quota.h>


static char Py_quotaon__doc__[] =
"quotaon(path, which, quotafile): turn filesystem quota on";

static PyObject *
Py_quotaon(PyObject *self, PyObject *args)
{
    int which;
    char *path, *quotafile;

    if (!PyArg_ParseTuple(args, "sis:quotaon", &path, &which, &quotafile))
        return NULL;

    if (quotactl(path, QCMD(Q_QUOTAON, which), 0, (void*)quotafile) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}


static char Py_quotaoff__doc__[] =
"quotaoff(path, which): turn filesystem quota off";

static PyObject *
Py_quotaoff(PyObject *self, PyObject *args)
{
    int which;
    char *path;

    if (!PyArg_ParseTuple(args, "si:quotaoff", &path, &which))
        return NULL;

    if (quotactl(path, QCMD(Q_QUOTAOFF, which), 0, 0) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}


static char Py_getquota__doc__[] =
"getquota(path, which, uid): get filesystem quotas; `which` must be GRPQUOTA or USRQUOTA";

static PyObject *
Py_getquota(PyObject *self, PyObject *args)
{
    struct dqblk qp;
    int uid, which;
    char *path;
    PyObject *r;

    if (!PyArg_ParseTuple(args,"sii:getquota", &path, &which, &uid))
        return NULL;

    if (quotactl(path, QCMD(Q_GETQUOTA, which), uid, (void*)&qp) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    r = PyDict_New();

    SETDICT_LONG(r, "bhardlimit",   qp.dqb_bhardlimit);
    SETDICT_LONG(r, "bsoftlimit",   qp.dqb_bsoftlimit);
    SETDICT_LONG(r, "curblocks",    qp.dqb_curblocks);
    SETDICT_LONG(r, "ihardlimit",   qp.dqb_ihardlimit);
    SETDICT_LONG(r, "isoftlimit",   qp.dqb_isoftlimit);
    SETDICT_LONG(r, "curinodes",    qp.dqb_curinodes);
    SETDICT_INT (r, "btime",        qp.dqb_btime);
    SETDICT_INT (r, "itime",        qp.dqb_itime);

    return r;
}


static char Py_setquota__doc__[] =
"setquota(path, which, uid[, {name}={value}]): set filesystem quotas;"
" `which` must be GRPQUOTA or USRQUOTA. Available names are bhardlimit, "
"bsoftlimit, ihardlimit, isoftlimit, btime, itime.";

static PyObject *
Py_setquota(PyObject *self, PyObject *args, PyObject *kwargs)
{
    static char *kwlist[] = {
        "path", "which", "uid", "bhardlimit", "bsoftlimit",
        "ihardlimit", "isoftlimit", "btime", "itime", NULL
    };
    struct dqblk qp;
    long long bhardlimit = -1, bsoftlimit = -1, ihardlimit = -1, isoftlimit = -1,
              btime = -1, itime = -1;
    int uid, which;
    char *path;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs,
            "sii|LLLLii:setquota", kwlist, &path, &which, &uid,
            &bhardlimit, &bsoftlimit, &ihardlimit, &isoftlimit, &btime, &itime))
        return NULL;

    if (bhardlimit < 0 or bsoftlimit < 0 or ihardlimit < 0 or isoftlimit < 0 or
        btime < 0 or itime < 0) {
        if (quotactl(path, QCMD(Q_GETQUOTA, which), uid, (void*)&qp) == -1) {
            PyErr_SetFromErrno(PyExc_OSError);
            return NULL;
        }
        if (bhardlimit >= 0) qp.dqb_bhardlimit = bhardlimit;
        if (bsoftlimit >= 0) qp.dqb_bsoftlimit = bsoftlimit;
        if (ihardlimit >= 0) qp.dqb_ihardlimit = ihardlimit;
        if (isoftlimit >= 0) qp.dqb_isoftlimit = isoftlimit;
        if (btime >= 0) qp.dqb_btime = btime;
        if (itime >= 0) qp.dqb_itime = itime;
    } else {
        qp.dqb_bhardlimit = bhardlimit;     qp.dqb_bsoftlimit = bsoftlimit;
        qp.dqb_ihardlimit = ihardlimit;     qp.dqb_isoftlimit = isoftlimit;
        qp.dqb_btime = btime;               qp.dqb_itime= itime;
    }

    if (quotactl(path, QCMD(Q_SETQUOTA, which), uid, (void*)&qp) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}


static char Py_quotasync__doc__[] =
"quotasync(path, which): sync filesystem quota";

static PyObject *
Py_quotasync(PyObject *self, PyObject *args)
{
    int which;
    char *path;

    if (!PyArg_ParseTuple(args, "si:quotasync", &path, &which))
        return NULL;

    if (quotactl(path, QCMD(Q_SYNC, which), 0, 0) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

#endif

/*
 * ex: ts=8 sts=4 et
 */
