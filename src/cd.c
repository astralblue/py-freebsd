/*
 * cd.c
 *
 * cdcontrol(1) and cd utilities
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 17:23:56 $
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

METHOD (cd)


/*
 * Function Bindings
 */
#else

#include <sys/cdio.h>

staticforward PyTypeObject PyCD_Type;

typedef struct {
    PyObject_HEAD
    char *device;
    int fd;
} cdobject;

#define SELF ((cdobject *)(self))

static void
cd_dealloc(PyObject *self)
{
    free(SELF->device);
    close(SELF->fd);
    PyObject_Del(self);
}

static char cd_eject__doc__[] =
"eject(): eject the disc";

static PyObject *
cd_eject(PyObject *self)
{
    (void)ioctl(SELF->fd, CDIOCALLOW);
    if (ioctl(SELF->fd, CDIOCEJECT) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

static char cd_close__doc__[] =
"close(): inject the disc";

static PyObject *
cd_close(PyObject *self)
{
    (void)ioctl(SELF->fd, CDIOCALLOW);
    if (ioctl(SELF->fd, CDIOCCLOSE) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    Py_INCREF(Py_None);
    return Py_None;
}

#undef SELF

static PyMethodDef cd_methods[] = {
    {"eject", (PyCFunction)cd_eject, METH_NOARGS, cd_eject__doc__},
    {"close", (PyCFunction)cd_close, METH_NOARGS, cd_close__doc__},
    {NULL,      NULL}       /* sentinel */
};

statichere PyTypeObject PyCD_Type = {
    PyObject_HEAD_INIT(NULL)
    ob_size:        0,
    tp_name:        "cd",
    tp_basicsize:   sizeof(cdobject),
    tp_itemsize:    0,
    tp_dealloc:     (destructor)cd_dealloc,
    tp_getattro:    PyObject_GenericGetAttr,
    tp_flags:       Py_TPFLAGS_DEFAULT,
    tp_methods:     cd_methods,
};


static char Py_cd__doc__[] =
"cd(device): open cd device";

static PyObject *
Py_cd(PyObject *self, PyObject *args)
{
    char *device;
    cdobject *obj;
    int fd;

    if (! PyArg_ParseTuple(args, "s:cd", &device))
        return NULL;

    if ((fd = open(device, O_RDWR)) == -1) {
        PyErr_SetFromErrno(PyExc_OSError);
        return NULL;
    }

    if ((obj = PyObject_New(cdobject, &PyCD_Type)) == NULL) {
        close(fd);
        return NULL;
    }

    obj->fd = fd;
    obj->device = strdup(device);

    return (PyObject*) obj;
}

#endif

/*
 * $Id: cd.c,v 1.3 2002/06/14 17:23:56 perky Exp $
 * ex: ts=8 sts=4 et
 */
