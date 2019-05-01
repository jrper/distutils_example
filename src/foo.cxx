#include <Python.h>

#define NO_IMPORT_ARRAY
#define PY_ARRAY_UNIQUE_SYMBOL PickerObject_ARRAY_API
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

#include <iostream>
#include <vector>

#include "foo.h"


extern "C" {

  static PyObject* foo_new(PyTypeObject* type, PyObject *args, PyObject *kw)
  {
    foo *self = (foo *) type->tp_alloc(type, 0);
    return (PyObject *) self;

  }

  static PyObject* get_name(PyObject* pyself, void *closure) {
    foo *self = (foo *) pyself;
    if (self->name[0]) {
      return PyString_FromString(self->name);
    } else {
      Py_RETURN_NONE;
    }
  }

  static int set_name(PyObject* pyself, PyObject* o, void *closure) {
    foo *self = (foo *) pyself;
    strncpy(self->name, PyString_AsString(o), 255);
    return 0;
  } 

  static int foo_init(PyObject *pyself, PyObject *args, PyObject *kw)
  { 
    if (!pyself) return -1;
    foo* self = (foo*) pyself;

    return 0;
  }

  static void foo_dealloc(PyObject *self)
  {
    foo *p = (foo*) self;
    Py_TYPE(self)->tp_free(self);
  }

  PyObject* foo_call(PyObject *self, PyObject *args, PyObject *kw)
  {
   
    Py_RETURN_NONE;

  }


  static PyObject* foo_repr(PyObject* self) {
    foo *p = (foo *) self;
    char buf[500];
    sprintf(buf, "%s ", Py_TYPE(self)->tp_name) ;
    return PyUnicode_FromString(buf);
  }

  static PyMethodDef foo_methods[] = {
    //    { (char*)"nearest", (PyCFunction) vtk_extrasPickerNearest, METH_VARARGS|METH_KEYWORDS, (char*) "Get value at nearest point in domain."},
    {NULL}
  };

  static PyGetSetDef foo_getset[] = {
    { (char*)"name", get_name, set_name, (char*)"Get/set data name.", NULL},
    { NULL}
  };

  static PyTypeObject fooType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "bar.foo",            /*tp_name*/
    sizeof(foo),       /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    foo_dealloc,       /*tp_dealloc*/
    0,                         /*tp_print PSEUDODEPRECATED*/
    0,                         /*tp_getattr DEPRECATED*/
    0,                         /*tp_setattr DEPRECATED*/
    0,                         /*tp_compare*/
    foo_repr,          /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    foo_call,          /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,        /* tp_flags */
    "Example python object.", /* tp_doc */
    0,  /* tp_traverse */
    0,  /* tp_clear */
    0,  /* tp_richcompare */
    0,  /* tp_weaklistoffset */
    0,  /* tp_iter: __iter__() method */
    0,  /* tp_iternext: next() method */
    foo_methods,                    /* tp_methods */
    0,                    /* tp_members */
    foo_getset, /* tp_getset */
    0, /* tp_base */
    0, /* tp_dict */
    0, /* tp_descr_get */
    0, /* tp_descr_set */
    0, /* tp_dictoffset */
    foo_init, /* tp_init */
    0, /* tp_alloc */
    foo_new, /* tp_new */
    0, /* tp_free Low-level free-memory routine */
    0 /* tp_is_gc For PyObject_IS_GC */
  };

  PyObject* foo_NEW(){
    foo* object = PyObject_NEW(foo, &fooType);
    return (PyObject*) object;
  }

  int foo_Check(PyObject* ob)
  {
    return PyObject_IsInstance(ob, (PyObject*) &foo_Type);
  }
  
  PyTypeObject* foo_Type() {
    return &fooType;
  }
}
