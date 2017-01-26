/*
 * pwdb.c
 *
 * passwd-related bindings
 *
 * Author  : Hye-Shik Chang <perky@fallin.lv>
 * Date    : $Date: 2002/06/14 10:35:22 $
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

METHOD (getpwnam)
METHOD (getpwuid)
METHOD_NOARGS (getpwent)


/*
 * Function Bindings
 */
#else

#include <pwd.h>


static PyObject *
PyObject_FromPasswd(struct passwd *pwd)
{
    PyObject *r;

    r = PyDict_New();
    SETDICT_STR(r, "name",      pwd->pw_name);
    SETDICT_STR(r, "passwd",    pwd->pw_passwd);
    SETDICT_INT(r, "uid",       pwd->pw_uid);
    SETDICT_INT(r, "gid",       pwd->pw_gid);
    SETDICT_INT(r, "change",    pwd->pw_change);
    SETDICT_STR(r, "class",     pwd->pw_class);
    SETDICT_STR(r, "gecos",     pwd->pw_gecos);
    SETDICT_STR(r, "dir",       pwd->pw_dir);
    SETDICT_STR(r, "shell",     pwd->pw_shell);
    SETDICT_INT(r, "expire",    pwd->pw_expire);
    SETDICT_INT(r, "fields",    pwd->pw_fields);

    return r;
}


static char Py_getpwuid__doc__[] =
"getpwuid(uid): get password entry from passwd database by uid";

static PyObject *
Py_getpwuid(PyObject *self, PyObject *args)
{
    struct passwd *pwd;
    int uid;

    if (! PyArg_ParseTuple(args, "i:getpwuid", &uid))
        return NULL;

    if ((pwd = getpwuid((uid_t)uid)) == NULL) {
        PyErr_Format(ErrorObject, "no such uid %d", uid);
        return NULL;
    }

    return PyObject_FromPasswd(pwd);
}

static char Py_getpwnam__doc__[] =
"getpwnam(name): get password entry from passwd database by name";

static PyObject *
Py_getpwnam(PyObject *self, PyObject *args)
{
    struct passwd *pwd;
    char *name;

    if (! PyArg_ParseTuple(args, "s:getpwnam", &name))
        return NULL;

    if ((pwd = getpwnam(name)) == NULL) {
        PyErr_Format(ErrorObject, "no such user %s", name);
        return NULL;
    }

    return PyObject_FromPasswd(pwd);
}

static char Py_getpwent__doc__[] =
"getpwent(): get whole password entry from passwd database";

static PyObject *
Py_getpwent(PyObject *self)
{
    PyObject *r, *m;
    struct passwd *pwd;

    setpwent();
    r = PyList_New(0);

    while((pwd = getpwent())) {
        m = PyObject_FromPasswd(pwd);
        PyList_Append(r, m);
        Py_DECREF(m);
    }
    endpwent();

    return r;
}

#endif
