#include <iostream>
#include "Python.h"

#define PY_ARRAY_UNIQUE_SYMBOL PickerObject_ARRAY_API
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

#include "foo.h"

#if PY_MAJOR_VERSION < 3
#define PyBytes_AsString PyString_AsString
#define PyBytes_FromString PyString_FromString
#endif


extern "C" {

  static PyObject *myMethod(PyObject *self, PyObject *args) {

    char* mystring;
    PyArg_ParseTuple(args, "s", &mystring);

    std::cout << mystring;    

    Py_RETURN_NONE;

  }

  static long count=0;

  static PyObject *myKeywordMethod(PyObject *self, PyObject *args,
				   PyObject *kwargs) {

    int stride=1;
    static char *kwlist[] = {"stride", NULL};
    PyArg_ParseTupleAndKeywords(args, kwargs, "i", kwlist, &stride);

    std::cout << stride;
    count = count + stride;

    PyObject* out = PyLong_FromLong(count);

    return out;
  }

  static char barDocString[] = "Example module.";

  static PyMethodDef barMethods[] = {  
    { (char *)"myMethod", (PyCFunction) myMethod, 
      METH_VARARGS, (char*) "myMethod docstring."},
    { (char *)"myKeywordMethod", (PyCFunction) myKeywordMethod, 
      METH_VARARGS|METH_KEYWORDS, (char*) "myKeywordMethod docstring."},
    { NULL, NULL, 0, NULL }
  };

PyObject * pyVersion = PyBytes_FromString(VERSION_STRING);

#if PY_MAJOR_VERSION >= 3
    static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "bar",     /* m_name */
        barDocString,  /* m_doc */
        -1,                  /* m_size */
        barMethods,    /* m_methods */
        NULL,                /* m_reload */
        NULL,                /* m_traverse */
        NULL,                /* m_clear */
        NULL,                /* m_free */
    };
#endif

#if PY_MAJOR_VERSION >= 3
  PyMODINIT_FUNC PyInit_bar() {

    PyObject* m = PyModule_Create(&moduledef);
    if (m == NULL) return NULL;
    import_array();

    Py_INCREF(pyVersion);
    PyModule_AddObject(m,"__version__", pyVersion);

    if (PyType_Ready(foo_Type()) < 0)  return NULL;

    Py_INCREF(foo_Type());
    PyModule_AddObject(m,"foo", (PyObject*)foo_Type());

    return m;
  }

#else
  PyMODINIT_FUNC initbar() {

    PyObject* m = Py_InitModule3("bar", barMethods, barDocString);
    if (m == NULL) return;
    import_array();

    Py_INCREF(pyVersion);
    PyModule_AddObject(m,"__version__", pyVersion);

    if (PyType_Ready(foo_Type()) < 0)  return;

    Py_INCREF(foo_Type());
    PyModule_AddObject(m,"foo", (PyObject*)foo_Type());

    return;
  }
#endif
}
