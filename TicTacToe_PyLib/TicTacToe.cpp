#include"pch.h"
#define PY_SSIZE_T_CLEAN
#include<Python.h>
#include "libstrings.h"
#define SetState(pos,num) self->state=self->state|(num << pos*2)
#define GetState(pos) ((self->state >> pos*2)%0x4)
#define FASTRETURN(re) if (re + 1) { return Py_BuildValue("i", re); }
//定义结构体
typedef struct {
    PyObject_HEAD
        int state;
} TicTacToe;
//释放内存
static void
tttDealloc(TicTacToe* self)
{
    Py_TYPE(self)->tp_free((PyObject*)self);
}
//新建
static PyObject*
tttNew(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
    TicTacToe* self;
    self = (TicTacToe*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->state = 0;
    }
    return (PyObject*)self;
}
//初始化
static int
tttInit(TicTacToe* self, PyObject* args, PyObject* kwds)
{
    self->state = 0x0;
    return 0;
}
//禁止修改state
static int
tttSetState(TicTacToe* self, PyObject* value, void* closure) {
    PyErr_SetString(PyExc_AttributeError, EXP_SETSTATE);
    return -1;
}
static PyObject *
//获取state
tttGetState(TicTacToe* self, void* closure) {
    return Py_BuildValue("((i,i,i),(i,i,i),(i,i,i))",
        GetState(6), GetState(7), GetState(8),
        GetState(3), GetState(4), GetState(5), 
        GetState(0), GetState(1), GetState(2));
}
static int CheckTable[8][3] = { {0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6} };
static void
Check(int* result, TicTacToe* self) {
    int i, dat[3];
    for (i = 0; i < 8; i++) {
        dat[0] = GetState(CheckTable[i][0]);
        dat[1] = GetState(CheckTable[i][1]);
        dat[2] = GetState(CheckTable[i][2]);
        if ((dat[0] == dat[1]) && (dat[1] == dat[2]) && dat[0]) {
            *result = dat[0];
            return;
        }
    }
    int count = 0;
    for (i = 0; i < 9; i++) {
        if (GetState(i))
            count++;
    }
    *result = (count > 8) ? 0 : -1;
    return;
}
static PyObject*
next(TicTacToe* self, PyObject* args, PyObject* kwds)
{
    int result;
    Check(&result, self);
    FASTRETURN(result)
    static char* kwlist[] = { (char*)CLASS_NEXT_FIRSTARG,(char*)CLASS_NEXT_SECONDARG, NULL };
    int f = -1, s = -1;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ii", kwlist,&f, &s)) {
        PyErr_SetString(PyExc_TypeError, EXP_ARGS);
        return NULL;
    }
    
    if ((f < -1) || (s < -1) || (f > 8) || (s > 8)) {
        PyErr_SetString(PyExc_IndexError, EXP_INDEX_OVER);
        return NULL;
    }
    if ((f == s && f!= -1) || GetState(f) || GetState(s)) {
        PyErr_SetString(PyExc_IndexError, EXP_INDEX_USED);
        return NULL;
    }
    if (f != -1) {
        SetState(f, 0x1);
        Check(&result, self);
        FASTRETURN(result)
    }
    if (s != -1) {
        SetState(s, 0x2);
        Check(&result, self);
    }
    return Py_BuildValue("i", result);
}
//注册模块
static PyModuleDef tttModule = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = MODULE_NAME,
    .m_doc = MODULE_DOC,
    .m_size = -1,
};
//注册方法
static PyMethodDef tttMethods[] = {
    {CLASS_NEXT_NAME, (PyCFunction)next, METH_VARARGS | METH_KEYWORDS,
     CLASS_NEXT_DOC
    },
    {NULL}  /* Sentinel */
};
//注册属性获取器
static PyGetSetDef tttGetsetters[] = {
    {CLASS_STATE_NAME, (getter)tttGetState, (setter)tttSetState,
     CLASS_STATE_DOC, NULL},
    {NULL}  /* Sentinel */
};
//注册类
static PyTypeObject tttTyp = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = CLASS_NAME,
    .tp_basicsize = sizeof(TicTacToe),
    .tp_itemsize = 0,
    .tp_dealloc = (destructor)tttDealloc,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_doc = CLASS_DOC,
    .tp_methods = tttMethods,
    //.tp_members = tttMembers,
    .tp_getset = tttGetsetters,
    .tp_init = (initproc)tttInit,
    .tp_new = tttNew,
};
PyMODINIT_FUNC
PyInit_TicTacToe(void) {
    PyObject* m;
    if (PyType_Ready(&tttTyp) < 0)
        return NULL;

    m = PyModule_Create(&tttModule);
    if (m == NULL)
        return NULL;

    Py_INCREF(&tttTyp);
    if (PyModule_AddObject(m, MODULE_NAME, (PyObject*)&tttTyp) < 0) {
        Py_DECREF(&tttTyp);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}