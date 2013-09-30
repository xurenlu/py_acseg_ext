/*
 *
 */
#include <Python.h>
#include "structmember.h"
#include "acseg_util.h"
#include "acseg_tree.h"

typedef struct {
	PyObject_HEAD	
	acseg_index_t *index;
} AcIndex;

static PyObject *
AcIndex_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    AcIndex *self;

    self = (AcIndex *)type->tp_alloc(type, 0);

	self->index = NULL;

    return (PyObject *)self;

}

static int 
AcIndex_init(AcIndex *self, PyObject *args, PyObject *kwds)
{
	self->index = acseg_index_init();

	return 0;
}

static void
AcIndex_dealloc(AcIndex *self)
{
	acseg_destory_index(&(self->index));
	self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
AcIndex_load_dict(AcIndex *self, PyObject *args)
{
	const char *fpath;
	if (!PyArg_ParseTuple(args, "s", &fpath)){
		PyErr_SetString(PyExc_TypeError, "load dict takes exactly one argument (0 given)");
		return NULL;	
	}

	if (!acseg_index_load(self->index, fpath)){
		PyErr_SetString(PyExc_TypeError, "load dict takes exactly one argument (0 given)");
		return NULL;
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
AcIndex_add_word(AcIndex *self, PyObject *args)
{
	acseg_str_t phrase;
	if (!PyArg_ParseTuple(args, "s#", &(phrase.data), &(phrase.len))){
		PyErr_SetString(PyExc_TypeError, "add word takes exactly one argument (0 given)");
		return NULL;	
	}

	if (!acseg_index_add(self->index, &phrase)){
		PyErr_SetString(PyExc_TypeError, "add word failed");
		return NULL;
	}
	Py_INCREF(Py_None);
	return Py_None;
}

PyObject *
AcIndex_fix_index(AcIndex *self, PyObject *args)
{
	acseg_index_fix(self->index);
	Py_INCREF(Py_None);
	return Py_None;
}

PyObject *
AcIndex_full_seg(AcIndex *self, PyObject *args)
{
	int i;

	acseg_str_t text;

	acseg_str_t *phrase;

	acseg_result_t * seg_result;

	acseg_list_item_t *result_item;

	PyObject* item_list;
    int k;
    k=0;
    int x;
    x=0;
	if (!PyArg_ParseTuple(args, "s#|ii", &(text.data), &(text.len),&k,&x)){
		PyErr_SetString(PyExc_TypeError, "full_seg takes exactly one argument or two argument");
		return NULL;	
	}
    if(x==0)
	seg_result = acseg_full_seg(self->index, &text,k);
    if(x==2){
	seg_result = acseg_full_seg2(self->index, &text,k);
    }
    if(x==3){
	seg_result = acseg_full_seg3(self->index, &text,k);
    }

	if (!seg_result){
		return PyList_New(0);
	}

	i = 0;
    result_item = seg_result->list->first;
    item_list = PyList_New(seg_result->num);
	while(result_item){
		phrase = (acseg_str_t *) result_item->data;	
		PyList_SetItem(item_list, i, Py_BuildValue("s#", phrase->data, phrase->len));
		result_item = result_item->next;
		i = i + 1;
	}

	acseg_destory_result(&seg_result);

    return item_list;
}

static PyMethodDef AcIndex_methods[] = {
	{
		"load_dict", 
		(PyCFunction)AcIndex_load_dict, 
		METH_VARARGS,
		"load dict from file, one word one line"
	},
	{
		"add_word", 
		(PyCFunction)AcIndex_add_word, 
		METH_VARARGS,
		"add a word to dict"
	},
	{
		"fix", 
		(PyCFunction)AcIndex_fix_index, 
		METH_VARARGS,
		"fix ac index"
	},
	{
		"full_seg", 
		(PyCFunction)AcIndex_full_seg, 
		METH_VARARGS,
		"do full seg"
	},

	{NULL}  /*  Sentinel */
};


static PyTypeObject AcIndexType = {
	PyObject_HEAD_INIT(NULL)
	0, /* ob_size*/
	"acseg.AcIndex", /* tp_name*/
	sizeof(AcIndex),           /* tp_basicsize*/
	0, /* tp_itemsize*/
	(destructor)AcIndex_dealloc, /* tp_dealloc*/
	0, /* tp_print*/
	0, /* tp_getattr*/
	0, /* tp_setattr*/
	0, /* tp_compare*/
	0, /* tp_repr*/
	0, /* tp_as_number*/
	0, /* tp_as_sequence*/
	0, /* tp_as_mapping*/
	0, /* tp_hash */
	0, /* tp_call*/
	0, /* tp_str*/
	0, /* tp_getattro*/
	0, /* tp_setattro*/
	0, /* tp_as_buffer*/
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags*/
	"AcIndex objects",           /*  tp_doc */
	0, /*  tp_traverse */
	0, /*  tp_clear */
	0, /*  tp_richcompare */
	0, /*  tp_weaklistoffset */
	0, /*  tp_iter */
	0, /*  tp_iternext */
	AcIndex_methods, /*  tp_methods */
	0, /*  tp_members */
	0, /*  tp_getset */
	0, /*  tp_base */
	0, /*  tp_dict */
	0, /*  tp_descr_get */
	0, /*  tp_descr_set */
	0, /*  tp_dictoffset */
	(initproc)AcIndex_init, /*  tp_init */
	NULL, /*  tp_alloc */
	AcIndex_new, /*  tp_new */
};

static PyMethodDef acseg_methods[] = {
	/*
	{
		"filter_keywords", 
		(PyCFunction)FkwDict_full_seg,
		METH_VARARGS,
		"alias to fkw_full_seg, just for fun"
	},
	*/

	{NULL}  /*  Sentinel */
};

#ifndef PyMODINIT_FUNC /*  declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC
initacseg(void)
{
	PyObject* m;

    if (PyType_Ready(&AcIndexType) < 0)
        return;

	m = Py_InitModule3("acseg", acseg_methods,
			"create filter keywords extension");

	Py_INCREF(&AcIndexType);
	PyModule_AddObject(m, "AcIndex", (PyObject *)&AcIndexType);
}
