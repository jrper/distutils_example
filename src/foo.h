/* @(#)foo.h
 */

#ifndef _FOO_H
#define _FOO_H 1

#include <Python.h>

extern "C" {

  typedef struct {
    PyObject_HEAD
    char name[255];
  } foo;

  PyObject* foo_NEW();
  int foo_Check(PyObject*);
  PyTypeObject* foo_Type();

};

#endif /* _FOO_H */

