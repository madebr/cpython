/*
 *    Interface to the ncurses menu library
 *    Original version by Ben Trofatter
 */

/* Release Number */

static char PyCursesVersion[] = "1.0";

/* Includes */

#include "Python.h"

#include "py_curses.h"

#include <menu.h>

typedef struct {
    PyObject *PyCursesError;
    PyObject *PyCursesMenu_Type;
    PyObject *PyCursesItem_Type;
} _curses_menustate;

static inline _curses_menustate*
get_curses_menustate(PyObject *module)
{
    void *state = PyModule_GetState(module);
    assert(state != NULL);
    return (_curses_menustate *)state;
}

static int
_curses_menu_clear(PyObject *m)
{
    Py_CLEAR(get_curses_menustate(m)->PyCursesError);
    return 0;
}

static int
_curses_menu_traverse(PyObject *m, visitproc visit, void *arg)
{
    Py_VISIT(Py_TYPE(m));
    Py_VISIT(get_curses_menustate(m)->PyCursesError);
    return 0;
}

static void
_curses_menu_free(void *m)
{
    _curses_menu_clear((PyObject *) m);
}

static struct PyModuleDef _curses_menumodule;

#define _curses_menustate_global \
((_curses_menustate *) PyModule_GetState(PyState_FindModule(&_curses_menumodule)))

/* Utility Functions */

/*
 * Check the return code from a curses function and return None
 * or raise an exception as appropriate.
 */

static PyObject *
PyCursesCheckERR(int code)
{
    //FIXME: menu sets errno
    if (code == E_OK) {
        Py_RETURN_NONE;
    } else {
        PyErr_SetFromErrno(_curses_menustate_global->PyCursesError);
        return NULL;
    }
}


static PyObject *
PyCursesCheckErrnoCode(int code, const char *fn)
{
    switch(code) {
    case E_OK:
        Py_RETURN_NONE;
    case E_BAD_ARGUMENT:
        return PyErr_Format(_curses_menustate_global->PyCursesError, "%s: Bad arguments (%d)", fn, code);
    default:
        return PyErr_Format(_curses_menustate_global->PyCursesError, "%s: %s (%d)", fn, strerror(code), code);
    }
}

/* Convert obj to a byte string object. Return:
    - NULL on error (exception is already set)
    - byte string object */
PyObject *
PyCurses_EncodedString(PyObject *obj, const char *encoding)
{
    // FIXME: convert to use clinic custom converter?
    if (PyUnicode_Check(obj)) {
        PyObject *bytes;
        char *str;
        bytes = PyUnicode_AsEncodedString(obj, encoding, NULL);
        if (bytes == NULL) {
            return NULL;
        }
        /* check for embedded null bytes */
        if (PyBytes_AsStringAndSize(bytes, &str, NULL) < 0) {
            Py_DECREF(bytes);
            return NULL;
        }
        return bytes;
    } else if (PyBytes_Check(obj)) {
        char *str;
        /* check for embedded null bytes */
        if (PyBytes_AsStringAndSize(obj, &str, NULL) < 0) {
            return NULL;
        }
        Py_INCREF(obj);
        return obj;
    }
    PyErr_Format(PyExc_TypeError, "expect bytes or str, got %s",
                 Py_TYPE(obj)->tp_name);
    return NULL;
}

/****************************************************************************
 The Item Object
*****************************************************************************/

/* Definition of the item object and item type */

typedef struct {
    PyObject_HEAD
    ITEM *item;
    PyObject *name;
    PyObject *description;
} PyCursesItemObject;

#define PyCursesItem_Check(ob) \
    ((PyObject*)Py_TYPE(ob) == _curses_menustate_global->PyCursesItem_Type)

/*[clinic input]
module _curses_menu
class _curses_menu.item "PyCursesItemObject *" "&PyCursesItem_Type"
class _curses_menu.menu "PyCursesMenuObject *" "&PyCursesMenu_Type"
[clinic start generated code]*/
/*[clinic end generated code: output=da39a3ee5e6b4b0d input=45ed9ddf8267477f]*/

static PyObject *
PyCursesItem_New(ITEM *item, PyObject *name, PyObject *description)
{
    PyCursesItemObject *io;

    io = PyObject_NEW(PyCursesItemObject,
                      (PyTypeObject *)(_curses_menustate_global)->PyCursesItem_Type);
    if (io == NULL) return NULL;
    io->item = item;
    io->name = name;
    io->description = description;
    return (PyObject *)io;
}

static void
PyCursesItem_Dealloc(PyCursesItemObject *io)
{
    PyObject *tp, *obj;
    tp = (PyObject *) Py_TYPE(io);
    obj = (PyObject *) item_userptr(io->item);
    if (obj != NULL) {
        (void)set_item_userptr(io->item, NULL);
        Py_DECREF(obj);
    }
    (void)free_item(io->item);
    Py_XDECREF(io->name);
    Py_XDECREF(io->description);
    PyObject_DEL(io);
    Py_DECREF(tp);
}

/*[clinic input]
_curses_menu.item.description

Return the description part of the current item.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_description_impl(PyCursesItemObject *self)
/*[clinic end generated code: output=c5a904fafd3d4281 input=8d8b9ce6787ca6e5]*/
{
    PyCursesInitialised;
    if (self->description) {
        Py_XINCREF(self->description);
        return self->description;
    } else {
        /* Valid output, it means no description */
        Py_RETURN_NONE;
    }
}

/*[clinic input]
_curses_menu.item.name

Return the name part of the current item.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_name_impl(PyCursesItemObject *self)
/*[clinic end generated code: output=01dacce2be86882a input=84b9ae7c24b2f8bf]*/
{
    PyCursesInitialised;
    if (self->name) {
        Py_XINCREF(self->name);
        return self->name;
    } else {
        /* Valid output, it means no name */
        Py_RETURN_NONE;
    }
}

/*[clinic input]
_curses_menu.item.set_userptr

    obj: object
    /

Set the item's user pointer to obj.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_set_userptr(PyCursesItemObject *self, PyObject *obj)
/*[clinic end generated code: output=4d40ad4056ec9fde input=90d1fa76721f7918]*/
{
    PyObject *oldobj;
    int rc;
    PyCursesInitialised;
    oldobj = (PyObject *)item_userptr(self->item);
    rc = set_item_userptr(self->item, (void*)obj);
    if (rc != E_OK) {
        return PyCursesCheckErrnoCode(rc, "set_item_userptr");
        return NULL;
    } else {
        /* Only incref obj and decref oldobj when set_item_usertpr was successful */
        Py_INCREF(obj);
        Py_XDECREF(oldobj);
    }
    return PyCursesCheckERR(rc);
}

/*[clinic input]
_curses_menu.item.userptr

Return the user pointer for the item.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_userptr_impl(PyCursesItemObject *self)
/*[clinic end generated code: output=348f497da26b74be input=9996fce9c399143e]*/
{
    PyObject *obj;
    PyCursesInitialised;
    obj = (PyObject *)item_userptr(self->item);
    if (obj == NULL) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "no userptr set");
        return NULL;
    }
    Py_INCREF(obj);
    return obj;
}

/*[clinic input]
_curses_menu.item.set_value

    value: bool
    /

Set the item's value.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_set_value_impl(PyCursesItemObject *self, int value)
/*[clinic end generated code: output=158d88e915a0f920 input=6e8128de615d2d64]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_item_value(self->item, value ? TRUE : FALSE);
    return PyCursesCheckErrnoCode(rc, "set_item_value");
}

/*[clinic input]
_curses_menu.item.value

Get the item's value.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_value_impl(PyCursesItemObject *self)
/*[clinic end generated code: output=f8bed792324426a0 input=dd44693a5974c791]*/
{
    bool v;
    PyCursesInitialised;
    v = item_value(self->item);
    return PyBool_FromLong(v);
}

/*[clinic input]
_curses_menu.item.visible

check visibility of a menu item

A  menu item is visible when it is in the portion of a posted menu that
is mapped onto the screen (if the menu is  scrollable,  in  particular,
this portion will be smaller than the whole menu).
[clinic start generated code]*/

static PyObject *
_curses_menu_item_visible_impl(PyCursesItemObject *self)
/*[clinic end generated code: output=c89c5d9f4cac8ff5 input=16d5a8aaca330bf8]*/
{
    bool v;
    PyCursesInitialised;
    v = item_visible(self->item);
    return PyBool_FromLong(v);
}

/*[clinic input]
_curses_menu.item.set_opts

    opts: unsigned_int(bitwise=True)

Set all the given item's option bits.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_set_opts_impl(PyCursesItemObject *self, unsigned int opts)
/*[clinic end generated code: output=21b984459fbd6703 input=fc7c29dff717a49a]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_item_opts(self->item, opts);
    return PyCursesCheckErrnoCode(rc, "set_item_opts");
}

/*[clinic input]
_curses_menu.item.opts_on

    opts: unsigned_int(bitwise=True)

Turns on the given option bits, and leave others alone.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_opts_on_impl(PyCursesItemObject *self, unsigned int opts)
/*[clinic end generated code: output=72e1388bc551225c input=eb9b1aec7d7063ad]*/
{
    int rc;
    PyCursesInitialised;
    rc = item_opts_on(self->item, opts);
    return PyCursesCheckErrnoCode(rc, "item_opts_on");
}

/*[clinic input]
_curses_menu.item.opts_off

    opts: unsigned_int(bitwise=True)

Turn off the given option bits, and leave others alone.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_opts_off_impl(PyCursesItemObject *self, unsigned int opts)
/*[clinic end generated code: output=bedac4f413ec925a input=25e65179ee661f25]*/
{
    int rc;
    PyCursesInitialised;
    rc = item_opts_off(self->item, opts);
    return PyCursesCheckErrnoCode(rc, "item_opts_off");
}

/*[clinic input]
_curses_menu.item.opts

Returns the item's current option bits
[clinic start generated code]*/

static PyObject *
_curses_menu_item_opts_impl(PyCursesItemObject *self)
/*[clinic end generated code: output=6efe5b442cb1a6c6 input=0b3e4a3e9dc07460]*/
{
    Item_Options opts;
    PyCursesInitialised;
    opts = item_opts(self->item);
    return PyLong_FromUnsignedLong(opts);
}

/*[clinic input]
_curses_menu.item.index

Get the index of this item in the menu.
[clinic start generated code]*/

static PyObject *
_curses_menu_item_index_impl(PyCursesItemObject *self)
/*[clinic end generated code: output=7ef8a29a7664bf45 input=47cd18061d1123e8]*/
{
    int index;
    PyCursesInitialised;
    index = item_index(self->item);
    if (index == ERR) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "item_index");
        return NULL;
    }
    return PyLong_FromLong(index);
}

/****************************************************************************
 The Menu Object
*****************************************************************************/

/* Definition of the menu object and menu type */

typedef struct {
    PyObject_HEAD
    MENU *menu;
    ITEM **items;
    PyObject *tuple_items;
    PyCursesWindowObject *win;
    PyCursesWindowObject *sub;
    PyObject *item_init_hook;
    PyObject *item_term_hook;
    PyObject *menu_init_hook;
    PyObject *menu_term_hook;
} PyCursesMenuObject;

#define PyCursesMenu_Check(ob) \
    ((PyObject*)Py_TYPE(ob) == _curses_menustate_global->PyCursesMenu_Type)



/* We keep a linked list of PyCursesMenuObjects, lom. A list should
   suffice, I don't expect more than a handful or at most a few
   dozens of panel objects within a typical program. */
typedef struct _list_of_menus {
    PyCursesMenuObject *mo;
    struct _list_of_menus *next;
} list_of_menus;

/* list anchor */
static list_of_menus *lom;

/* Insert a new menu object into lom */
static int
insert_lom(PyCursesMenuObject *mo)
{
    list_of_menus *new;

    if ((new = (list_of_menus *)PyMem_Malloc(sizeof(list_of_menus))) == NULL) {
        PyErr_NoMemory();
        return -1;
    }
    new->mo = mo;
    new->next = lom;
    lom = new;
    return 0;
}

/* Remove the menu object from lom */
static void
remove_lom(PyCursesMenuObject *mo)
{
    list_of_menus *temp, *n;

    temp = lom;
    if (temp->mo == mo) {
        lom = temp->next;
        PyMem_Free(temp);
        return;
    }
    while (temp->next == NULL || temp->next->mo != mo) {
        if (temp->next == NULL) {
            PyErr_SetString(PyExc_RuntimeError,
                            "remove_lom: can't find MENU Object");
            return;
        }
        temp = temp->next;
    }
    n = temp->next->next;
    PyMem_Free(temp->next);
    temp->next = n;
    return;
}

static void
_check_convert_item_tuple_to_array(PyObject *tuple, ITEM ***items)
{
    ITEM **raw_items;
    Py_ssize_t i, nb;
    if (!PyTuple_Check(tuple)) {
        PyErr_SetString(PyExc_ValueError, "items needs to be a tuple");
        return;
    }
    nb = PyTuple_GET_SIZE(tuple);
    for (i = 0; i < nb; i++) {
        if (!PyCursesItem_Check(PyTuple_GET_ITEM(tuple, i))) {
            PyErr_SetString(PyExc_ValueError, "values of tuple must be menu items");
            return;
        }
    }
    raw_items = (ITEM **) PyMem_Calloc(nb + 1, sizeof(ITEM *));
    if (raw_items == NULL) {
        PyErr_NoMemory();
        return;
    }
    for (i = 0; i < nb; i++) {
        raw_items[i] = ((PyCursesItemObject *)PyTuple_GET_ITEM(tuple, i))->item;
    }
    raw_items[nb] = NULL;
    *items = raw_items;
}

/* Allocation and deallocation of Menu Objects */

static PyObject *
PyCursesMenu_New(MENU *menu, ITEM **items, PyObject *tuple_items)
{
    PyCursesMenuObject *mo;
    PyCursesInitialised;
    mo = PyObject_NEW(PyCursesMenuObject,
                      (PyTypeObject *)(_curses_menustate_global)->PyCursesMenu_Type);
    if (mo == NULL) {
        PyMem_Free(items);
        return NULL;
    }
    if (insert_lom(mo) < 0) {
        Py_DECREF(mo);
        return NULL;
    }
    mo->menu = menu;
    mo->items = items;
    Py_INCREF(tuple_items);
    mo->tuple_items = tuple_items;
    mo->win = NULL;
    mo->sub = NULL;
    mo->item_init_hook = NULL;
    mo->item_term_hook = NULL;
    mo->menu_init_hook = NULL;
    mo->menu_term_hook = NULL;
    return (PyObject*)mo;
}

static void
PyCursesMenu_Dealloc(PyCursesMenuObject *mo)
{
    PyObject *obj;
    obj = (PyObject *) menu_userptr(mo->menu);
    if (obj != NULL) {
        (void)set_menu_userptr(mo->menu, NULL);
        Py_DECREF(obj);
    }

    remove_lom(mo);
    Py_XDECREF(mo->item_init_hook);
    Py_XDECREF(mo->item_term_hook);
    Py_XDECREF(mo->menu_init_hook);
    Py_XDECREF(mo->menu_term_hook);
    Py_XDECREF(mo->win);
    Py_XDECREF(mo->sub);
    Py_DECREF(mo->tuple_items);
    (void)free_menu(mo->menu);
    PyMem_Free(mo->items);
    PyObject_DEL(mo);
}

/* Return the menu object that corresponds to men */
static PyCursesMenuObject *
find_mo(MENU *men) {
    list_of_menus *temp;
    for (temp = lom; temp; temp = temp->next) {
        if (temp->mo->menu == men) {
            return temp->mo;
        }
    }
    return NULL;    /* not found!? */
}

/* Native C hook wrapper functions */

static void
_item_init_hook(MENU *menu) {
    PyGILState_STATE gstate;
    PyCursesMenuObject *pymenu;
    PyObject *args, *res;
    pymenu = find_mo(menu);
    if (pymenu == NULL) {
        return;
    }
    gstate = PyGILState_Ensure();
    args = PyTuple_Pack(1, pymenu);
    if (args == NULL) {
        return;
    }
    res = PyObject_Call(pymenu->item_init_hook, args, NULL);
    Py_XDECREF(res);
    Py_DECREF(args);
    PyGILState_Release(gstate);
}

static void
_item_term_hook(MENU *menu) {
    PyGILState_STATE gstate;
    PyCursesMenuObject *pymenu;
    PyObject *args, *res;
    pymenu = find_mo(menu);
    if (pymenu == NULL) {
        return;
    }
    gstate = PyGILState_Ensure();
    args = PyTuple_Pack(1, pymenu);
    if (args == NULL) {
        return;
    }
    res = PyObject_Call(pymenu->item_term_hook, args, NULL);
    Py_XDECREF(res);
    Py_DECREF(args);
    PyGILState_Release(gstate);
}

static void
_menu_init_hook(MENU *menu) {
    PyGILState_STATE gstate;
    PyCursesMenuObject *pymenu;
    PyObject *args, *res;
    pymenu = find_mo(menu);
    if (pymenu == NULL) {
        return;
    }
    gstate = PyGILState_Ensure();
    args = PyTuple_Pack(1, pymenu);
    if (args == NULL) {
        return;
    }
    res = PyObject_Call(pymenu->menu_init_hook, args, NULL);
    Py_XDECREF(res);
    Py_DECREF(args);
    PyGILState_Release(gstate);
}

static void
_menu_term_hook(MENU *menu) {
    PyGILState_STATE gstate;
    PyCursesMenuObject *pymenu;
    PyObject *args, *res;
    pymenu = find_mo(menu);
    if (pymenu == NULL) {
        return;
    }
    gstate = PyGILState_Ensure();
    args = PyTuple_Pack(1, pymenu);
    if (args == NULL) {
        return;
    }
    res = PyObject_Call(pymenu->menu_term_hook, args, NULL);
    Py_XDECREF(res);
    Py_DECREF(args);
    PyGILState_Release(gstate);
}

/*[clinic input]
_curses_menu.menu.fore

Returns the foreground attribute.

This is the highlight used for selected menu items.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_fore_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=c52d4701f8b465e4 input=626a0619bfcf47c0]*/
{
    chtype attr;
    PyCursesInitialised;
    attr = menu_fore(self->menu);
    return PyLong_FromUnsignedLong(attr);
}

/*[clinic input]
_curses_menu.menu.set_fore

    fore: unsigned_int(bitwise=True)

Set the foreground attribute.

This is the highlight used for selected menu items.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_fore_impl(PyCursesMenuObject *self, unsigned int fore)
/*[clinic end generated code: output=c3280c10b062082c input=8f717e2b3b1de84e]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_menu_fore(self->menu, fore);
    return PyCursesCheckErrnoCode(rc, "menu_set_fore");
}

/*[clinic input]
_curses_menu.menu.back

Returns the background attribute.

This is the highlight used for selectable (but not currently selected)
menu items.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_back_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=7055afb92a891a4f input=a66e91d4db5c91fc]*/
{
    chtype attr;
    PyCursesInitialised;
    attr = menu_back(self->menu);
    return PyLong_FromUnsignedLong(attr);
}

/*[clinic input]
_curses_menu.menu.set_back

    back: unsigned_int(bitwise=True)

Set the background attribute.

This is the highlight used for selectable (but not currently selected)
menu items.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_back_impl(PyCursesMenuObject *self, unsigned int back)
/*[clinic end generated code: output=bf2fe7a972c25f4b input=512ec1582b787692]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_menu_back(self->menu, back);
    return PyCursesCheckErrnoCode(rc, "set_menu_back");
}

/*[clinic input]
_curses_menu.menu.grey

Returns the grey attribute.

This is the highlight used for un-selectable menu items in menus that
permit more than one selection.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_grey_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=4f887ca2900abfb3 input=c47a3fd0426542e2]*/
{
    chtype attr;
    PyCursesInitialised;
    attr = menu_grey(self->menu);
    return PyLong_FromUnsignedLong(attr);
}

/*[clinic input]
_curses_menu.menu.set_grey

    grey: unsigned_int(bitwise=True)

Set the grey attribute.

This is the highlight used for un-selectable menu items in menus that
permit more than one selection.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_grey_impl(PyCursesMenuObject *self, unsigned int grey)
/*[clinic end generated code: output=fe4d66857e0ec50b input=62fd4cd0e6540a69]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_menu_grey(self->menu, grey);
    return PyCursesCheckErrnoCode(rc, "set_menu_back");
}

/*[clinic input]
_curses_menu.menu.pad

Returns the pad character.

This is the character used to fill the space between the name and description
parts of a menu item.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_pad_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=95822b7c5e57d5ce input=fab5a43436c5fbdd]*/
{
    int pad;
    PyCursesInitialised;
    pad = menu_pad(self->menu);
    return PyLong_FromUnsignedLong(pad);
}

/*[clinic input]
_curses_menu.menu.set_pad

    pad: int

Set the pad character..

This is the character used to fill the space between the name and description
parts of a menu item.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_pad_impl(PyCursesMenuObject *self, int pad)
/*[clinic end generated code: output=8e0d9573942788df input=da0394889d254a57]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_menu_pad(self->menu, pad);
    return PyCursesCheckErrnoCode(rc, "set_menu_back");
}

/*[clinic input]
_curses_menu.menu.items

Returns the item of the given menu.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_items_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=30ab05e03dc63ee7 input=4737f4e941b2125d]*/
{
    PyCursesInitialised;
    Py_INCREF(self->tuple_items);
    return self->tuple_items;
}

/*[clinic input]
_curses_menu.menu.set_items

    items: object
        Tuple with new items

Changes the items of the given menu.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_items_impl(PyCursesMenuObject *self, PyObject *items)
/*[clinic end generated code: output=9115f16eb609ec3e input=ecb0008685bf67c1]*/
{
    int rc;
    ITEM **raw_items;
    PyCursesInitialised;
    raw_items = NULL;
    _check_convert_item_tuple_to_array(items, &raw_items);
    if (raw_items == NULL) {
        return NULL;
    }

    rc = set_menu_items(self->menu, raw_items);
    if (rc != E_OK) {
        PyMem_Free(raw_items);
        return PyCursesCheckErrnoCode(rc, "set_menu_items");
    }

    PyMem_Free(self->items);
    Py_DECREF(self->tuple_items);

    self->items = raw_items;
    self->tuple_items = items;
    Py_INCREF(items);
    Py_RETURN_NONE;
}

/*[clinic input]
_curses_menu.menu.count

Return the count of items in menu.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_count_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=7de876e36c9d6a2b input=7c4d08e2c13e3e3f]*/
{
    return PyLong_FromLong(PyTuple_GET_SIZE(self->tuple_items));
}

/*[clinic input]
_curses_menu.menu.userptr

Get the menu user pointer field.

Every menu and every menu item has a field that can be used to hold
application-specific data (that is, the menu-driver code leaves it
alone).
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_userptr_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=264e1a4d8efc17a0 input=82cdf1d9d2d4a194]*/
{
    PyObject *obj;
    PyCursesInitialised;
    obj = (PyObject *)menu_userptr(self->menu);
    if (obj == NULL) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "no userptr set");
        return NULL;
    }
    Py_INCREF(obj);
    return obj;
}

/*[clinic input]
_curses_menu.menu.set_userptr

    obj: object

Set the menu user pointer field.

Every menu and every menu item has a field that can be used to hold
application-specific data (that is, the menu-driver code leaves it
alone).
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_userptr_impl(PyCursesMenuObject *self, PyObject *obj)
/*[clinic end generated code: output=c36fdc71209912de input=57682cd2d6a74b05]*/
{
    PyObject *oldobj;
    int rc;
    PyCursesInitialised;
    oldobj = (PyObject *)menu_userptr(self->menu);
    rc = set_menu_userptr(self->menu, (void*)obj);
    if (rc != E_OK) {
        return PyCursesCheckErrnoCode(rc, "set_menu_userptr");
    } else {
        /* Only incref obj and decref oldobj when set_menu_usertpr was successful */
        Py_INCREF(obj);
        Py_XDECREF(oldobj);
    }
    Py_RETURN_NONE;
}

/*[clinic input]
_curses_menu.menu.mark

Get the menu mark string.

In order to make menu selections visible on older terminals without
highlighting or color capability, the menu library marks selected items
in a menu with a prefix string.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_mark_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=9312d96aa903869e input=de3d4425415495b9]*/
{
    const char *mark;
    PyCursesInitialised;
    mark = menu_mark(self->menu);
    if (mark == NULL) {
        Py_RETURN_NONE;
    }
    return PyBytes_FromString(mark);
}


//FIXME: use Py_buffer(accept={buffer, str})
/*[clinic input]
_curses_menu.menu.set_mark

    obj: object

Set the menu mark string.

In order to make menu selections visible on older terminals without
highlighting or color capability, the menu library marks selected items
in a menu with a prefix string.

Calling set_mark with None will abolish the mark
string. Note that changing the length of the mark string for a menu
while the menu is posted is likely to produce unhelpful behavior.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_mark_impl(PyCursesMenuObject *self, PyObject *obj)
/*[clinic end generated code: output=0aad2a92608f8d69 input=0c2a50ee90ff9d9c]*/
{
    PyObject *mark_obj;
    char *mark_str;
    int rc;
    PyCursesInitialised;

    mark_obj = PyCurses_EncodedString(obj, NULL);
    if (mark_obj == NULL) {
        return NULL;
    }
    rc = PyBytes_AsStringAndSize(mark_obj, &mark_str, NULL);
    if (rc < 0) {
        return NULL;
    }
    rc = set_menu_mark(self->menu, mark_str);
    Py_DECREF(mark_obj);
    return PyCursesCheckErrnoCode(rc, "set_menu_mark");
}


static Py_ssize_t
_menu_find_item(PyCursesMenuObject *menu, ITEM *item) {
    Py_ssize_t i, nb;
    nb = PyTuple_GET_SIZE(menu->tuple_items);
    for (i = 0; i < nb; i++) {
        if (menu->items[i] == item) {
            return i;
        }
    }
    return -1;
}

/*[clinic input]
_curses_menu.menu.current_item

Get the current item (the item on which the menu cursor is positioned)

Return None, if no current item is selected.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_current_item_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=0e9427afcd67a5ea input=73d498c3f7f635f9]*/
{
    ITEM *current;
    Py_ssize_t idx_item;
    PyObject *py_item;
    PyCursesInitialised;
    current = (ITEM *)current_item(self->menu);
    if (current == NULL) {
        Py_RETURN_NONE;
    }
    idx_item = _menu_find_item(self, current);
    if (idx_item < 0) {
        PyErr_SetString(PyExc_RuntimeError, "Cannot find item object returned by current_item");
        return NULL;
    }
    py_item = PyTuple_GET_ITEM(self->tuple_items, idx_item);
    Py_INCREF(py_item);
    return py_item;
}


// FIXME: add item clinic CConverter for PyCursesItemObject?

/*[clinic input]
_curses_menu.menu.set_current_item

    item: object
        curses item object

Set the current item (the item on which the menu cursor is positioned)
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_current_item_impl(PyCursesMenuObject *self,
                                        PyObject *item)
/*[clinic end generated code: output=9b38ff992b2413e9 input=e120eda9922f845d]*/
{
    int rc;
    PyCursesInitialised;
    PyCursesItemObject *py_item;
    if (!PyCursesItem_Check(item)) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "argument must be an item or None");
        return NULL;
    }
    py_item = (PyCursesItemObject *) item;
    rc = set_current_item(self->menu, py_item->item);
    return PyCursesCheckErrnoCode(rc, "set_current_item");
}

/*[clinic input]
_curses_menu.menu.top_row

Get the index of the top menu row being displayed.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_top_row_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=3f7d8affc8822d8f input=1591c11e1a61bd8b]*/
{
    int row_index;
    PyCursesInitialised;
    row_index = top_row(self->menu);
    if (row_index == ERR) {
        return PyErr_Format(_curses_menustate_global->PyCursesError, "top_row");
    }
    return PyLong_FromLong(row_index);
}

/*[clinic input]
_curses_menu.menu.set_top_row

    row: int

Set the index of the top menu row being displayed.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_top_row_impl(PyCursesMenuObject *self, int row)
/*[clinic end generated code: output=7d2cbfc4c4a88fff input=9bc5e82e4e21882e]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_top_row(self->menu, row);
    return PyCursesCheckErrnoCode(rc, "set_top_row");
}

/*[clinic input]
_curses_menu.menu.format

Get the maximum display size.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_format_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=ae7058e2cdbc5bbc input=c4046f7522d6e17c]*/
{
    int rows, cols;
    PyCursesInitialised;
    menu_format(self->menu, &rows, &cols);
    return Py_BuildValue("(ii)", rows, cols);
}

/*[clinic input]
_curses_menu.menu.set_format

    rows: int

    cols: int

Set the maximum display size.

If this size is too small to display all menu items,
the menu will be made scrollable.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_format_impl(PyCursesMenuObject *self, int rows,
                                  int cols)
/*[clinic end generated code: output=37899965660e4d09 input=ed98e8d05fa493a2]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_menu_format(self->menu, rows, cols);
    return PyCursesCheckErrnoCode(rc, "set_menu_format");
}

/*[clinic input]
_curses_menu.menu.spacing

Get the spacing information for the menu.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_spacing_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=b2f181e5b862616b input=567c22c21acab788]*/
{
    int description, rows, cols, rc;
    PyCursesInitialised;
    rc = menu_spacing(self->menu, &description, &rows, &cols);
    if (rc != E_OK) {
        return PyCursesCheckErrnoCode(rc, "menu_spacing");
    }
    return Py_BuildValue("(iii)", description, rows, cols);
}

/*[clinic input]
_curses_menu.menu.set_spacing

    description: int
       number of spaces between an item name and an item description

    rows: int
       number of rows that are used for an item.

    cols: int
        number of blanks between columns of items

Set the spacing information for the menu.

If this size is too small to display all menu items,
the menu will be made scrollable.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_spacing_impl(PyCursesMenuObject *self, int description,
                                   int rows, int cols)
/*[clinic end generated code: output=d0988d22d6922458 input=7072cf7511344346]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_menu_spacing(self->menu, description, rows, cols);
    return PyCursesCheckErrnoCode(rc, "set_menu_spacing");
}

/*[clinic input]
_curses_menu.menu.post

Displays the menu to its associated subwindow.

To trigger physical display of the subwindow,use refresh or some
equivalent curses routine (the implicit doupdate triggered by an curses
input request will do). post resets the selection status of all
items.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_post_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=13669533065dfd99 input=f647ed8c34dc659c]*/
{
    int rc;
    PyCursesInitialised;
    rc = post_menu(self->menu);
    return PyCursesCheckErrnoCode(rc, "post_menu");
}

/*[clinic input]
_curses_menu.menu.unpost

Erases the menu from its associated subwindow.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_unpost_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=abdea16f9a668c02 input=6de953334c01792d]*/
{
    int rc;
    PyCursesInitialised;
    rc = unpost_menu(self->menu);
    return PyCursesCheckErrnoCode(rc, "post_menu");
}

/*[clinic input]
_curses_menu.menu.pattern

Get the pattern buffer.

Every menu has an associated pattern match buffer. As input events
that are printable characters come in, they are appended to this match
buffer and tested for a match,
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_pattern_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=5d464b7aea16a188 input=233e7cba8b9a5c00]*/
{
    const char *pattern;
    PyCursesInitialised;
    pattern = menu_pattern(self->menu);
    return PyBytes_FromString(pattern);
}

/*[clinic input]
_curses_menu.menu.set_pattern

    pattern: object

Sets the pattern buffer and try to find the first matching item.

Every menu has an associated pattern match buffer. As input events
that are printable characters come in, they are appended to this match
buffer and tested for a match,
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_pattern_impl(PyCursesMenuObject *self,
                                   PyObject *pattern)
/*[clinic end generated code: output=6623d448c0c0ebe0 input=22f534451455262d]*/
{
    int rc;
    char *pattern_str;
    PyObject *pattern_pybytes;
    PyCursesInitialised;
    pattern_pybytes = PyCurses_EncodedString(pattern, NULL);
    if (pattern_pybytes == NULL) {
        return NULL;
    }
    rc = PyBytes_AsStringAndSize(pattern_pybytes, &pattern_str, NULL);
    if (rc < 0) {
        Py_DECREF(pattern_pybytes);
        return NULL;
    }
    rc = set_menu_pattern(self->menu, pattern_str);
    Py_DECREF(pattern_pybytes);
    return PyCursesCheckErrnoCode(rc, "set_menu_pattern");
}

/*[clinic input]
_curses_menu.menu.driver

    c: int

Funnel input events to the menu.    
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_driver_impl(PyCursesMenuObject *self, int c)
/*[clinic end generated code: output=bc33e8531d3a4ff2 input=e83112f5c0f2bea9]*/
{
    int rc;
    rc = menu_driver(self->menu, c);
    return PyCursesCheckErrnoCode(rc, "menu_driver");
}

/*[clinic input]
_curses_menu.menu.set_opts

    opts: unsigned_int(bitwise=True)

Set all the given menu's option bits.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_opts_impl(PyCursesMenuObject *self, unsigned int opts)
/*[clinic end generated code: output=42dc8674d2c521c9 input=31a1c344a6f99173]*/
{
    int rc;
    PyCursesInitialised;
    rc = set_menu_opts(self->menu, opts);
    return PyCursesCheckErrnoCode(rc, "set_menu_opts");
}

/*[clinic input]
_curses_menu.menu.opts_on

    opts: unsigned_int(bitwise=True)

Turns on the given option bits, and leave others alone.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_opts_on_impl(PyCursesMenuObject *self, unsigned int opts)
/*[clinic end generated code: output=950c73d3401cdfba input=68ff481861e1cc4e]*/
{
    int rc;
    PyCursesInitialised;
    rc = menu_opts_on(self->menu, opts);
    return PyCursesCheckErrnoCode(rc, "menu_opts_on");
}

/*[clinic input]
_curses_menu.menu.opts_off

    opts: unsigned_int(bitwise=True)

Turn off the given option bits, and leave others alone.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_opts_off_impl(PyCursesMenuObject *self, unsigned int opts)
/*[clinic end generated code: output=e5f49655d746a08d input=a4e5ce5862e244b0]*/
{
    int rc;
    PyCursesInitialised;
    rc = menu_opts_off(self->menu, opts);
    return PyCursesCheckErrnoCode(rc, "menu_opts_off");
}

/*[clinic input]
_curses_menu.menu.opts

Returns the menu's current option bits
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_opts_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=7f2489a5801f8b0b input=400fe07a66753484]*/
{
    Menu_Options opts;
    PyCursesInitialised;
    opts = menu_opts(self->menu);
    return PyLong_FromUnsignedLong(opts);
}

/*[clinic input]
_curses_menu.menu.set_item_init

    func: object

Set hook to be called at menu-post time and each time the selected item changes.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_item_init_impl(PyCursesMenuObject *self,
                                     PyObject *func)
/*[clinic end generated code: output=aeeb974a3c413666 input=1f98f7de1ee221ec]*/
{
    int rc;
    PyCursesInitialised;
    if (!PyCallable_Check(func)) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "Argument must be a callable");
        return NULL;
    }
    self->item_init_hook = func;
    Py_INCREF(func);
    rc = set_item_init(self->menu, _item_init_hook);
    return PyCursesCheckErrnoCode(rc, "set_item_init");
}

/*[clinic input]
_curses_menu.menu.item_init

Get hook to be called at menu-post time and each time the selected item changes.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_item_init_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=5be98936f2383a33 input=03dd8d184b7a4725]*/
{
    PyCursesInitialised;
    if (self->item_init_hook == NULL) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "No item_init hook set");
        return NULL;
    }
    Py_INCREF(self->item_init_hook);
    return self->item_init_hook;
}

/*[clinic input]
_curses_menu.menu.set_item_term

    func: object

Set hook to be called at menu-unpost time and each time the selected item changes (before the change).
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_item_term_impl(PyCursesMenuObject *self,
                                     PyObject *func)
/*[clinic end generated code: output=d54d4c5a6b9ea57b input=68ea3ce952a6a623]*/
{
    int rc;
    PyCursesInitialised;
    if (!PyCallable_Check(func)) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "Argument must be a callable");
        return NULL;
    }
    self->item_term_hook = func;
    Py_INCREF(func);
    rc = set_item_term(self->menu, _item_term_hook);
    return PyCursesCheckErrnoCode(rc, "set_item_term");
}

/*[clinic input]
_curses_menu.menu.item_term

Get hook to be called at menu-unpost time and each time the selected item changes (before the change).
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_item_term_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=ce89569171533dbf input=84f8194126d49b9b]*/
{
    PyCursesInitialised;
    if (self->item_term_hook == NULL) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "No item_term hook set");
        return NULL;
    }
    Py_INCREF(self->item_term_hook);
    return self->item_term_hook;
}

/*[clinic input]
_curses_menu.menu.set_menu_init

    func: object

Set hook to be called at menu-post time and just after the top row on the menu changes once it is posted.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_menu_init_impl(PyCursesMenuObject *self,
                                     PyObject *func)
/*[clinic end generated code: output=6cea8a30283dbacd input=850a7d10f9bfde1a]*/
{
    int rc;
    PyCursesInitialised;
    if (!PyCallable_Check(func)) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "Argument must be a callable");
        return NULL;
    }
    self->menu_init_hook = func;
    Py_INCREF(func);
    rc = set_menu_init(self->menu, _menu_init_hook);
    return PyCursesCheckErrnoCode(rc, "set_menu_init");
}

/*[clinic input]
_curses_menu.menu.menu_init

Get hook to be called at menu-post time and just after the top row on the menu changes once it is posted.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_menu_init_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=743bcb673879bf61 input=bce273f9d1320f46]*/
{
    PyCursesInitialised;
    if (self->menu_init_hook == NULL) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "No menu_init hook set");
        return NULL;
    }
    Py_INCREF(self->menu_init_hook);
    return self->menu_init_hook;
}

/*[clinic input]
_curses_menu.menu.set_menu_term

    func: object

Set hook to be called at menu-unpost time and just before the top row on the menu changes once it is posted.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_menu_term_impl(PyCursesMenuObject *self,
                                     PyObject *func)
/*[clinic end generated code: output=527fc06e9f6745b8 input=25b11e12955babc1]*/
{
    int rc;
    PyCursesInitialised;
    if (!PyCallable_Check(func)) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "Argument must be a callable");
        return NULL;
    }
    self->menu_term_hook = func;
    Py_INCREF(func);
    rc = set_menu_term(self->menu, _menu_term_hook);
    return PyCursesCheckErrnoCode(rc, "set_menu_term");
}

/*[clinic input]
_curses_menu.menu.menu_term

Get hook to be called at menu-unpost time and just before the top row on the menu changes once it is posted.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_menu_term_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=37823a7a524aaf5e input=a410764dd1e98fea]*/
{
    PyCursesInitialised;
    if (self->menu_term_hook == NULL) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "No menu_term hook set");
        return NULL;
    }
    Py_INCREF(self->menu_term_hook);
    return self->menu_term_hook;
}

/*[clinic input]
_curses_menu.menu.pos_cursor

Restore the cursor to the current position associated with the menu's selected item.

This is useful after curses routines have been called to do screen-painting in response to a
menu select.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_pos_cursor_impl(PyCursesMenuObject *self)
/*[clinic end generated code: output=d209672077b2f2a5 input=2318c474df8bb79d]*/
{
    int rc;
    rc = pos_menu_cursor(self->menu);
    return PyCursesCheckErrnoCode(rc, "pos_menu_cursor");
}

/*[clinic input]
_curses_menu.menu.set_win

    win: object

Set menu window.

Every menu has an associated pair of curses windows. The menu window
displays any title and border associated with the window; the menu sub-
window displays the items of the menu that are currently available for
selection.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_win_impl(PyCursesMenuObject *self, PyObject *win)
/*[clinic end generated code: output=3d66a4b206489b16 input=b9e5dbdd466d0cd3]*/
{
    int rc;
    WINDOW *cwin;
    if (win == Py_None) {
        cwin = NULL;
    } else if (!PyCursesWindow_Check(win)) {
        PyErr_SetString(PyExc_ValueError, "Arguments must be None or a curses window");
        return NULL;
    } else {
        cwin = ((PyCursesWindowObject *)win)->win;
    }
    rc = set_menu_win(self->menu, cwin);
    if (rc == E_OK) {
        Py_XDECREF(self->win);
        self->win = (PyCursesWindowObject *)win;
        Py_INCREF(win);
    }
    return PyCursesCheckErrnoCode(rc, "set_menu_win");
}

/*[clinic input]
_curses_menu.menu.set_sub

    win: object

Set sub window.

Every menu has an associated pair of curses windows. The menu window
displays any title and border associated with the window; the menu sub-
window displays the items of the menu that are currently available for
selection.
[clinic start generated code]*/

static PyObject *
_curses_menu_menu_set_sub_impl(PyCursesMenuObject *self, PyObject *win)
/*[clinic end generated code: output=36f8c7c3a7f11021 input=fda297e73f780d63]*/
{
    int rc;
    WINDOW *cwin;
    if (win == Py_None) {
        cwin = NULL;
    } else if (!PyCursesWindow_Check(win)) {
        PyErr_SetString(PyExc_ValueError, "Arguments must be None or a curses window");
        return NULL;
    } else {
        cwin = ((PyCursesWindowObject *)win)->win;
    }
    rc = set_menu_sub(self->menu, cwin);
    if (rc == E_OK) {
        Py_XDECREF(self->sub);
        self->sub = (PyCursesWindowObject *)win;
        Py_INCREF(win);
    }
    return PyCursesCheckErrnoCode(rc, "set_menu_sub");
}

/* -------------------------------------------------------*/
// Global functions

/*[clinic input]
_curses_menu.new_item

    name: object
        Name.
    description: object = NULL
        Description.

Create a new item and initialize it from name and description.
[clinic start generated code]*/

static PyObject *
_curses_menu_new_item_impl(PyObject *module, PyObject *name,
                           PyObject *description)
/*[clinic end generated code: output=887d60fc42e524ad input=d31c11881b5fcddf]*/
{
    int rc;
    PyObject *bytes_name, *bytes_description;
    char *chars_name, *chars_description;
    const char *encoding;
    ITEM *item;
    PyObject *py_item;
    PyCursesInitialised
    encoding = PyCursesEncoding(NULL);

    bytes_name = PyCurses_EncodedString(name, encoding);
    if (bytes_name == NULL) {
        return NULL;
    }
    rc = PyBytes_AsStringAndSize(bytes_name, &chars_name, NULL);
    if (rc < 0) {
        Py_DECREF(bytes_name);
        return NULL;
    }

    if (description == NULL) {
        bytes_description = NULL;
        chars_description = NULL;
    } else {
        bytes_description = PyCurses_EncodedString(description, encoding);
        if (bytes_description == NULL) {
            Py_DECREF(bytes_name);
            return NULL;
        }
        rc = PyBytes_AsStringAndSize(bytes_description, &chars_description, NULL);
        if (rc < 0) {
            Py_DECREF(bytes_name);
            Py_DECREF(bytes_description);
            return NULL;
        }
    }

    item = new_item(chars_name, chars_description);
    if (item == NULL) {
        Py_DECREF(bytes_name);
        Py_DECREF(bytes_description);
        return PyErr_SetFromErrno(_curses_menustate_global->PyCursesError);
    }

    py_item = PyCursesItem_New(item, bytes_name, bytes_description);
    return py_item;
}

/*[clinic input]
_curses_menu.new_menu

    items: object
        Tuple with items

Create a new menu connected to the specified items.
[clinic start generated code]*/

static PyObject *
_curses_menu_new_menu_impl(PyObject *module, PyObject *items)
/*[clinic end generated code: output=40c99e2c521b4353 input=1fbc32c18b3f7350]*/
{
    ITEM **raw_items;
    MENU *menu;
    raw_items = NULL;
    _check_convert_item_tuple_to_array(items, &raw_items);
    if (raw_items == NULL) {
        return NULL;
    }
    menu = new_menu(raw_items);
    if (menu == NULL) {
        PyMem_Free(raw_items);
        PyErr_SetFromErrno(_curses_menustate_global->PyCursesError);
    }
    return PyCursesMenu_New(menu, raw_items, items);
}

#if defined(NCURSES_VERSION)

/*[clinic input]
_curses_menu.request_name

    request: int

Returns the printable name of a menu request code.
[clinic start generated code]*/

static PyObject *
_curses_menu_request_name_impl(PyObject *module, int request)
/*[clinic end generated code: output=9504fc5ad5effc8c input=95381ab0798fc24b]*/
{
    const char *name;
    name = menu_request_name(request);
    if (name == NULL) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "Unknown request");
        return NULL;
    }
    return PyUnicode_FromString(name);
}

/*[clinic input]
_curses_menu.request_by_name

    name: str

Searches in the name-table for a request with the given name and return its request code.
[clinic start generated code]*/

static PyObject *
_curses_menu_request_by_name_impl(PyObject *module, const char *name)
/*[clinic end generated code: output=3acbf36a3dd71bb4 input=8ba6e05fb01e3fc2]*/
{
    int request;
    request = menu_request_by_name(name);
    if (request == E_NO_MATCH) {
        PyErr_SetString(_curses_menustate_global->PyCursesError, "Unknown name");
        return NULL;
    }
    return PyLong_FromLong(request);
}

#endif


/* -------------------------------------------------------*/

#include "clinic/_curses_menu.c.h"

/* -------------------------------------------------------*/

/* Item interface */

static PyMethodDef PyCursesItem_Methods[] = {
    _CURSES_MENU_ITEM_USERPTR_METHODDEF
    _CURSES_MENU_ITEM_SET_USERPTR_METHODDEF
    _CURSES_MENU_ITEM_VALUE_METHODDEF
    _CURSES_MENU_ITEM_SET_VALUE_METHODDEF
    _CURSES_MENU_ITEM_NAME_METHODDEF
    _CURSES_MENU_ITEM_DESCRIPTION_METHODDEF
    _CURSES_MENU_ITEM_OPTS_METHODDEF
    _CURSES_MENU_ITEM_SET_OPTS_METHODDEF
    _CURSES_MENU_ITEM_OPTS_OFF_METHODDEF
    _CURSES_MENU_ITEM_OPTS_ON_METHODDEF
    _CURSES_MENU_ITEM_INDEX_METHODDEF
    _CURSES_MENU_ITEM_VISIBLE_METHODDEF
    {NULL, NULL} /* sentinel */
};

static PyType_Slot PyCursesItem_Type_slots[] = {
    {Py_tp_dealloc, PyCursesItem_Dealloc},
    {Py_tp_methods, PyCursesItem_Methods},
    {0, 0},
};

static PyType_Spec PyCursesItem_Type_spec = {
    "_curses_menu.item",
    sizeof(PyCursesItemObject),
    0,
    Py_TPFLAGS_DEFAULT,
    PyCursesItem_Type_slots
};

/* -------------------------------------------------------*/

/* Menu interface */

static PyMethodDef PyCursesMenu_Methods[] = {
    _CURSES_MENU_MENU_BACK_METHODDEF
    _CURSES_MENU_MENU_SET_BACK_METHODDEF
    _CURSES_MENU_MENU_CURRENT_ITEM_METHODDEF
    _CURSES_MENU_MENU_SET_CURRENT_ITEM_METHODDEF
    _CURSES_MENU_MENU_FORE_METHODDEF
    _CURSES_MENU_MENU_SET_FORE_METHODDEF
    _CURSES_MENU_MENU_FORMAT_METHODDEF
    _CURSES_MENU_MENU_SET_FORMAT_METHODDEF
    _CURSES_MENU_MENU_GREY_METHODDEF
    _CURSES_MENU_MENU_SET_GREY_METHODDEF
    _CURSES_MENU_MENU_MARK_METHODDEF
    _CURSES_MENU_MENU_SET_MARK_METHODDEF
    _CURSES_MENU_MENU_PAD_METHODDEF
    _CURSES_MENU_MENU_SET_PAD_METHODDEF
    _CURSES_MENU_MENU_SPACING_METHODDEF
    _CURSES_MENU_MENU_SET_SPACING_METHODDEF
    _CURSES_MENU_MENU_TOP_ROW_METHODDEF
    _CURSES_MENU_MENU_SET_TOP_ROW_METHODDEF
    _CURSES_MENU_MENU_USERPTR_METHODDEF
    _CURSES_MENU_MENU_SET_USERPTR_METHODDEF
    _CURSES_MENU_MENU_PATTERN_METHODDEF
    _CURSES_MENU_MENU_SET_PATTERN_METHODDEF
    _CURSES_MENU_MENU_ITEMS_METHODDEF
    _CURSES_MENU_MENU_SET_ITEMS_METHODDEF
    _CURSES_MENU_MENU_ITEM_INIT_METHODDEF
    _CURSES_MENU_MENU_SET_ITEM_INIT_METHODDEF
    _CURSES_MENU_MENU_ITEM_TERM_METHODDEF
    _CURSES_MENU_MENU_SET_ITEM_TERM_METHODDEF
    _CURSES_MENU_MENU_MENU_INIT_METHODDEF
    _CURSES_MENU_MENU_SET_MENU_INIT_METHODDEF
    _CURSES_MENU_MENU_MENU_TERM_METHODDEF
    _CURSES_MENU_MENU_SET_MENU_TERM_METHODDEF
    _CURSES_MENU_MENU_COUNT_METHODDEF
    _CURSES_MENU_MENU_OPTS_METHODDEF
    _CURSES_MENU_MENU_SET_OPTS_METHODDEF
    _CURSES_MENU_MENU_OPTS_OFF_METHODDEF
    _CURSES_MENU_MENU_OPTS_ON_METHODDEF
    _CURSES_MENU_MENU_POST_METHODDEF
    _CURSES_MENU_MENU_UNPOST_METHODDEF
    _CURSES_MENU_MENU_DRIVER_METHODDEF
    _CURSES_MENU_MENU_POS_CURSOR_METHODDEF
    _CURSES_MENU_MENU_SET_SUB_METHODDEF
    _CURSES_MENU_MENU_SET_WIN_METHODDEF
    {NULL, NULL} /* sentinel */
};

static PyType_Slot PyCursesMenu_Type_slots[] = {
    {Py_tp_dealloc, PyCursesMenu_Dealloc},
    {Py_tp_methods, PyCursesMenu_Methods},
    {0, 0},
};

static PyType_Spec PyCursesMenu_Type_spec = {
    "_curses_menu.menu",
    sizeof(PyCursesMenuObject),
    0,
    Py_TPFLAGS_DEFAULT,
    PyCursesMenu_Type_slots
};

/* -------------------------------------------------------*/

/* List of functions defined in the module */

static PyMethodDef PyCurses_methods[] = {
    _CURSES_MENU_NEW_ITEM_METHODDEF
    _CURSES_MENU_NEW_MENU_METHODDEF
#if defined(NCURSES_VERSION)
    _CURSES_MENU_REQUEST_NAME_METHODDEF
    _CURSES_MENU_REQUEST_BY_NAME_METHODDEF
#endif
    {NULL,              NULL}           /* sentinel */
};


/* Initialization function for the module */

static struct PyModuleDef _curses_menumodule = {
    PyModuleDef_HEAD_INIT,
    "_curses_menu",
    NULL,
    sizeof(_curses_menustate),
    PyCurses_methods,
    NULL,
    _curses_menu_traverse,
    _curses_menu_clear,
    _curses_menu_free
};

PyMODINIT_FUNC
PyInit__curses_menu(void)
{
    PyObject *m, *d, *v;

    /* Create the module and add the functions */
    m = PyModule_Create(&_curses_menumodule);
    if (m == NULL)
        goto fail;
    d = PyModule_GetDict(m);

    /* Initialize object type */
    v = PyType_FromSpec(&PyCursesItem_Type_spec);
    if (v == NULL)
        goto fail;
    ((PyTypeObject *)v)->tp_new = NULL;
    get_curses_menustate(m)->PyCursesItem_Type = v;

    v = PyType_FromSpec(&PyCursesMenu_Type_spec);
    if (v == NULL)
        goto fail;
    ((PyTypeObject *)v)->tp_new = NULL;
    get_curses_menustate(m)->PyCursesMenu_Type = v;

    import_curses();
    if (PyErr_Occurred())
        goto fail;

    /* For exception _curses_menu.error */
    get_curses_menustate(m)->PyCursesError = PyErr_NewException("_curses_menu.error", NULL, NULL);
    PyDict_SetItemString(d, "error", get_curses_menustate(m)->PyCursesError);

    /* Make the version available */
    v = PyUnicode_FromString(PyCursesVersion);
    PyDict_SetItemString(d, "version", v);
    PyDict_SetItemString(d, "__version__", v);
    Py_DECREF(v);

    Py_INCREF(get_curses_menustate(m)->PyCursesItem_Type);
    PyModule_AddObject(m, "item",
                       (PyObject *)get_curses_menustate(m)->PyCursesItem_Type);
#if 0
    Py_INCREF(get_curses_menustate(m)->PyCursesMenu_Type);
    PyModule_AddObject(m, "menu",
                       (PyObject *)get_curses_menustate(m)->PyCursesMenu_Type);
#endif

    /* Set constants */

#define SetDictInt(string,ch)                               \
    do {                                                    \
        PyObject *o = PyLong_FromLong((long) (ch));         \
        if (o && PyDict_SetItemString(d, string, o) == 0) { \
            Py_DECREF(o);                                   \
        }                                                   \
    } while (0)

    /* Menu options: */

    SetDictInt("O_ONEVALUE",   O_ONEVALUE);
    SetDictInt("O_SHOWDESC",   O_SHOWDESC);
    SetDictInt("O_ROWMAJOR",   O_ROWMAJOR);
    SetDictInt("O_IGNORECASE", O_IGNORECASE);
    SetDictInt("O_SHOWMATCH",  O_SHOWMATCH);
    SetDictInt("O_NONCYCLIC",  O_NONCYCLIC);
    SetDictInt("O_MOUSE_MENU", O_MOUSE_MENU);

    /* Item options: */

    SetDictInt("O_SELECTABLE", O_SELECTABLE);

    /* Menu driver requests: */

    SetDictInt("REQ_LEFT_ITEM",     REQ_LEFT_ITEM);
    SetDictInt("REQ_RIGHT_ITEM",    REQ_RIGHT_ITEM);
    SetDictInt("REQ_UP_ITEM",       REQ_UP_ITEM);
    SetDictInt("REQ_DOWN_ITEM",     REQ_DOWN_ITEM);
    SetDictInt("REQ_SCR_ULINE",     REQ_SCR_ULINE);
    SetDictInt("REQ_SCR_DLINE",     REQ_SCR_DLINE);
    SetDictInt("REQ_SCR_DPAGE",     REQ_SCR_DPAGE);
    SetDictInt("REQ_SCR_UPAGE",     REQ_SCR_UPAGE);
    SetDictInt("REQ_FIRST_ITEM",    REQ_FIRST_ITEM);
    SetDictInt("REQ_LAST_ITEM",     REQ_LAST_ITEM);
    SetDictInt("REQ_NEXT_ITEM",     REQ_NEXT_ITEM);
    SetDictInt("REQ_PREV_ITEM",     REQ_PREV_ITEM);
    SetDictInt("REQ_TOGGLE_ITEM",   REQ_TOGGLE_ITEM);
    SetDictInt("REQ_CLEAR_PATTERN", REQ_CLEAR_PATTERN);
    SetDictInt("REQ_BACK_PATTERN",  REQ_BACK_PATTERN);
    SetDictInt("REQ_NEXT_MATCH",    REQ_NEXT_MATCH);
    SetDictInt("REQ_PREV_MATCH",    REQ_PREV_MATCH);

    SetDictInt("MIN_MENU_COMMAND",  MIN_MENU_COMMAND);
    SetDictInt("MAX_MENU_COMMAND",  MAX_MENU_COMMAND);
#undef SetDictInt
    return m;

fail:
    Py_XDECREF(m);
    return NULL;
}
