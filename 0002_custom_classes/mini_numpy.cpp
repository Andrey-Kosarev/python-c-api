#define PY_SSIZE_T_CLEAN
#include <vector>
#include <iostream>
#include <Python.h>

// definition of classes properties 
typedef struct {
    PyObject_HEAD
    /* Type-specific fields go here. */
    std::vector<double> vec;
} PyVectorObject;

// __init__ implementation
static int PyVector_init(PyVectorObject *self, PyObject *args, PyObject *kwds)
{
    PyObject *vec = NULL;
    
    //Parsing incoming tuple args (expecting only one param "O" - object), and storing it into vec
    if (!PyArg_ParseTuple(args, "O", &vec)){
        std::cout << "INCOMING PARAMS WRONG" << std::endl ;
        return -1;
    }

    // checking if the incoming parameter is a list
    if (!PyList_Check(vec)) {
        std::cout << "vec is not a list" << std::endl ;
        PyErr_SetString(PyExc_TypeError, "parameter must be a list");
        return NULL;
    }

    //storing size of the list into a variables
    Py_ssize_t list_size = PyList_Size(vec);
    

    // storing python list items into a c++ vector
    for(int i=0;i<list_size;i++){
        PyObject *item = PyList_GetItem(vec, i);
        double x = PyFloat_AsDouble(item);
        self->vec.push_back(x);
    }
    
    return 0;
}

//a method to calculate sum of the vector
static PyObject *sum(PyVectorObject *self, PyObject *Py_UNUSED(ignored)){
    double sum = 0;
    
    for(double i: self->vec){
        sum += i;
    }


    return PyFloat_FromDouble(sum);
}


// store all methods (just "sum" in this case) into the method def
static PyMethodDef PyVectorMethods[] = {
    {"sum", (PyCFunction) sum, METH_NOARGS, "Return the name, combining the first and last name"},
    {NULL}  /* Sentinel */
};


// define the PyVector class, 
static PyTypeObject PyVector = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "mini_numpy.PyVector",    // tp_name
    sizeof(PyVectorObject),   // tp_basicsize
    0,                        // tp_itemsize
    0,                        // tp_dealloc (you may need to define a deallocator if necessary)
    0,                        // tp_print (if used)
    0,                        // tp_getattr (if used)
    0,                        // tp_setattr (if used)
    0,                        // tp_reserved (if used)
    0,                        // tp_repr (if used)
    0,                        // tp_as_number (if used)
    0,                        // tp_as_sequence (if used)
    0,                        // tp_as_mapping (if used)
    0,                        // tp_hash (if used)
    0,                        // tp_call (if used)
    0,                        // tp_str (if used)
    0,                        // tp_getattro (if used)
    0,                        // tp_setattro (if used)
    0,                        // tp_as_buffer (if used)
    Py_TPFLAGS_DEFAULT,        // tp_flags
    "PyVector",                // tp_doc
    0,                        // tp_traverse (if used)
    0,                        // tp_clear (if used)
    0,                        // tp_richcompare (if used)
    0,                        // tp_weaklistoffset (if used)
    0,                        // tp_iter (if used)
    0,                        // tp_iternext (if used)
    PyVectorMethods,           // tp_methods
    0,                        // tp_members (if used)
    0,                        // tp_getset (if used)
    0,                        // tp_base (if used)
    0,                        // tp_dict (if used)
    0,                        // tp_descr_get (if used)
    0,                        // tp_descr_set (if used)
    0,                        // tp_dictoffset (if used)
    (initproc) PyVector_init, // tp_init (if used)
    0,                        // tp_alloc (if used)
    PyType_GenericNew,        // tp_new
    0,                        // tp_free (if used)
    0,                        // tp_is_gc (if used)
};


// 
static struct PyModuleDef mini_numpy = {
    PyModuleDef_HEAD_INIT,
    "mini_numpy",
    "Example module to demonstate creating custom classes in C-API",
    -1
};

PyMODINIT_FUNC PyInit_mini_numpy(void) {
    PyObject *m;
    if (PyType_Ready(&PyVector) < 0)
        return NULL;

    m = PyModule_Create(&mini_numpy);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyVector);
    if (PyModule_AddObject(m, "PyVector", (PyObject *) &PyVector) < 0) {
        Py_DECREF(&PyVector);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}
