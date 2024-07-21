#include <iostream>
#include <Python.h>
#include <string>

static PyObject* hello(PyObject* self, PyObject* args) {
    std::string greeting = "Hello Python C API!!!";
    std::cout << greeting << std::endl;
    Py_RETURN_NONE;
}

static PyObject* add_two_nums(PyObject* self, PyObject* args) {
    double x;
    double y;

    PyArg_ParseTuple(args, "dd", &x, &y);

    return PyFloat_FromDouble(x + y);
}

static PyObject* sum_list(PyObject* self, PyObject* args) {
    PyObject *list;

    // Parse the input tuple
    if (!PyArg_ParseTuple(args, "O", &list)) {
        return NULL;
    }

    // Ensure the input is a list
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "parameter must be a list");
        return NULL;
    }

    double sum = 0;
    int list_size = PyList_Size(list);


    for(int i=0;i<list_size;i++){
        PyObject *item = PyList_GetItem(list, i);
        sum += PyFloat_AsDouble(item);
    }


    return PyFloat_FromDouble(sum);
}



static PyMethodDef my_methods[] = {
    {"hello", hello, METH_VARARGS, "Prints a hello message"},
    {"add_two_nums", add_two_nums, METH_VARARGS, "Adds two nums"},
    {"sum_list", sum_list, METH_VARARGS, "Loops over a list"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef hello_c_api = {
    PyModuleDef_HEAD_INIT,
    "hello_c_api",
    "Example module that says hello",
    -1,
    my_methods
};

PyMODINIT_FUNC PyInit_hello_c_api(void) {
    return PyModule_Create(&hello_c_api);
}