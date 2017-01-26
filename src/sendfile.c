/*
 * sendfile.c
 *
 * sendfile binding
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

METHOD (sendfile)


/*
 * Function Bindings
 */
#else

#include <sys/uio.h>

/* TODO: headers and trailers are not supported yet. */
static char Py_sendfile__doc__[] =
"sendfile(fd, s, offset, nbytes[, headers, tailers]): send a file to a socket";

static PyObject *
Py_sendfile(PyObject *self, PyObject *args)
{
    int fd, s, res;
    off_t offset, sbytes;
    size_t nbytes;
    PyObject *headers = NULL, *tailers = NULL;
    
    if (! PyArg_ParseTuple(args, "iill|OO:sendfile", &fd, &s, &offset, &nbytes, &headers, &tailers))
        return NULL;
    
    if ((res = sendfile(fd, s, offset, nbytes, NULL, &sbytes, 0)) == -1) {
        if (errno == EAGAIN)
            return PyInt_FromLong(sbytes);
        else {
            PyErr_SetFromErrno(PyExc_OSError);
            return NULL;
        }
    }

    return PyInt_FromLong(sbytes);
}

#endif
