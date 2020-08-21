/*[clinic input]
preserve
[clinic start generated code]*/

PyDoc_STRVAR(_curses_menu_item_description__doc__,
"description($self, /)\n"
"--\n"
"\n"
"Return the description part of the current item.");

#define _CURSES_MENU_ITEM_DESCRIPTION_METHODDEF    \
    {"description", (PyCFunction)_curses_menu_item_description, METH_NOARGS, _curses_menu_item_description__doc__},

static PyObject *
_curses_menu_item_description_impl(PyCursesItemObject *self);

static PyObject *
_curses_menu_item_description(PyCursesItemObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_item_description_impl(self);
}

PyDoc_STRVAR(_curses_menu_item_name__doc__,
"name($self, /)\n"
"--\n"
"\n"
"Return the name part of the current item.");

#define _CURSES_MENU_ITEM_NAME_METHODDEF    \
    {"name", (PyCFunction)_curses_menu_item_name, METH_NOARGS, _curses_menu_item_name__doc__},

static PyObject *
_curses_menu_item_name_impl(PyCursesItemObject *self);

static PyObject *
_curses_menu_item_name(PyCursesItemObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_item_name_impl(self);
}

PyDoc_STRVAR(_curses_menu_item_set_userptr__doc__,
"set_userptr($self, obj, /)\n"
"--\n"
"\n"
"Set the item\'s user pointer to obj.");

#define _CURSES_MENU_ITEM_SET_USERPTR_METHODDEF    \
    {"set_userptr", (PyCFunction)_curses_menu_item_set_userptr, METH_O, _curses_menu_item_set_userptr__doc__},

PyDoc_STRVAR(_curses_menu_item_userptr__doc__,
"userptr($self, /)\n"
"--\n"
"\n"
"Return the user pointer for the item.");

#define _CURSES_MENU_ITEM_USERPTR_METHODDEF    \
    {"userptr", (PyCFunction)_curses_menu_item_userptr, METH_NOARGS, _curses_menu_item_userptr__doc__},

static PyObject *
_curses_menu_item_userptr_impl(PyCursesItemObject *self);

static PyObject *
_curses_menu_item_userptr(PyCursesItemObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_item_userptr_impl(self);
}

PyDoc_STRVAR(_curses_menu_item_set_value__doc__,
"set_value($self, value, /)\n"
"--\n"
"\n"
"Set the item\'s value.");

#define _CURSES_MENU_ITEM_SET_VALUE_METHODDEF    \
    {"set_value", (PyCFunction)_curses_menu_item_set_value, METH_O, _curses_menu_item_set_value__doc__},

static PyObject *
_curses_menu_item_set_value_impl(PyCursesItemObject *self, int value);

static PyObject *
_curses_menu_item_set_value(PyCursesItemObject *self, PyObject *arg)
{
    PyObject *return_value = NULL;
    int value;

    value = PyObject_IsTrue(arg);
    if (value < 0) {
        goto exit;
    }
    return_value = _curses_menu_item_set_value_impl(self, value);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_item_value__doc__,
"value($self, /)\n"
"--\n"
"\n"
"Get the item\'s value.");

#define _CURSES_MENU_ITEM_VALUE_METHODDEF    \
    {"value", (PyCFunction)_curses_menu_item_value, METH_NOARGS, _curses_menu_item_value__doc__},

static PyObject *
_curses_menu_item_value_impl(PyCursesItemObject *self);

static PyObject *
_curses_menu_item_value(PyCursesItemObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_item_value_impl(self);
}

PyDoc_STRVAR(_curses_menu_item_visible__doc__,
"visible($self, /)\n"
"--\n"
"\n"
"check visibility of a menu item\n"
"\n"
"A  menu item is visible when it is in the portion of a posted menu that\n"
"is mapped onto the screen (if the menu is  scrollable,  in  particular,\n"
"this portion will be smaller than the whole menu).");

#define _CURSES_MENU_ITEM_VISIBLE_METHODDEF    \
    {"visible", (PyCFunction)_curses_menu_item_visible, METH_NOARGS, _curses_menu_item_visible__doc__},

static PyObject *
_curses_menu_item_visible_impl(PyCursesItemObject *self);

static PyObject *
_curses_menu_item_visible(PyCursesItemObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_item_visible_impl(self);
}

PyDoc_STRVAR(_curses_menu_item_set_opts__doc__,
"set_opts($self, /, opts)\n"
"--\n"
"\n"
"Set all the given item\'s option bits.");

#define _CURSES_MENU_ITEM_SET_OPTS_METHODDEF    \
    {"set_opts", (PyCFunction)(void(*)(void))_curses_menu_item_set_opts, METH_FASTCALL|METH_KEYWORDS, _curses_menu_item_set_opts__doc__},

static PyObject *
_curses_menu_item_set_opts_impl(PyCursesItemObject *self, unsigned int opts);

static PyObject *
_curses_menu_item_set_opts(PyCursesItemObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"opts", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_opts", 0};
    PyObject *argsbuf[1];
    unsigned int opts;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    opts = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (opts == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_item_set_opts_impl(self, opts);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_item_opts_on__doc__,
"opts_on($self, /, opts)\n"
"--\n"
"\n"
"Turns on the given option bits, and leave others alone.");

#define _CURSES_MENU_ITEM_OPTS_ON_METHODDEF    \
    {"opts_on", (PyCFunction)(void(*)(void))_curses_menu_item_opts_on, METH_FASTCALL|METH_KEYWORDS, _curses_menu_item_opts_on__doc__},

static PyObject *
_curses_menu_item_opts_on_impl(PyCursesItemObject *self, unsigned int opts);

static PyObject *
_curses_menu_item_opts_on(PyCursesItemObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"opts", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "opts_on", 0};
    PyObject *argsbuf[1];
    unsigned int opts;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    opts = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (opts == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_item_opts_on_impl(self, opts);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_item_opts_off__doc__,
"opts_off($self, /, opts)\n"
"--\n"
"\n"
"Turn off the given option bits, and leave others alone.");

#define _CURSES_MENU_ITEM_OPTS_OFF_METHODDEF    \
    {"opts_off", (PyCFunction)(void(*)(void))_curses_menu_item_opts_off, METH_FASTCALL|METH_KEYWORDS, _curses_menu_item_opts_off__doc__},

static PyObject *
_curses_menu_item_opts_off_impl(PyCursesItemObject *self, unsigned int opts);

static PyObject *
_curses_menu_item_opts_off(PyCursesItemObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"opts", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "opts_off", 0};
    PyObject *argsbuf[1];
    unsigned int opts;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    opts = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (opts == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_item_opts_off_impl(self, opts);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_item_opts__doc__,
"opts($self, /)\n"
"--\n"
"\n"
"Returns the item\'s current option bits");

#define _CURSES_MENU_ITEM_OPTS_METHODDEF    \
    {"opts", (PyCFunction)_curses_menu_item_opts, METH_NOARGS, _curses_menu_item_opts__doc__},

static PyObject *
_curses_menu_item_opts_impl(PyCursesItemObject *self);

static PyObject *
_curses_menu_item_opts(PyCursesItemObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_item_opts_impl(self);
}

PyDoc_STRVAR(_curses_menu_item_index__doc__,
"index($self, /)\n"
"--\n"
"\n"
"Get the index of this item in the menu.");

#define _CURSES_MENU_ITEM_INDEX_METHODDEF    \
    {"index", (PyCFunction)_curses_menu_item_index, METH_NOARGS, _curses_menu_item_index__doc__},

static PyObject *
_curses_menu_item_index_impl(PyCursesItemObject *self);

static PyObject *
_curses_menu_item_index(PyCursesItemObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_item_index_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_fore__doc__,
"fore($self, /)\n"
"--\n"
"\n"
"Returns the foreground attribute.\n"
"\n"
"This is the highlight used for selected menu items.");

#define _CURSES_MENU_MENU_FORE_METHODDEF    \
    {"fore", (PyCFunction)_curses_menu_menu_fore, METH_NOARGS, _curses_menu_menu_fore__doc__},

static PyObject *
_curses_menu_menu_fore_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_fore(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_fore_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_fore__doc__,
"set_fore($self, /, fore)\n"
"--\n"
"\n"
"Set the foreground attribute.\n"
"\n"
"This is the highlight used for selected menu items.");

#define _CURSES_MENU_MENU_SET_FORE_METHODDEF    \
    {"set_fore", (PyCFunction)(void(*)(void))_curses_menu_menu_set_fore, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_fore__doc__},

static PyObject *
_curses_menu_menu_set_fore_impl(PyCursesMenuObject *self, unsigned int fore);

static PyObject *
_curses_menu_menu_set_fore(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"fore", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_fore", 0};
    PyObject *argsbuf[1];
    unsigned int fore;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    fore = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (fore == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_fore_impl(self, fore);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_back__doc__,
"back($self, /)\n"
"--\n"
"\n"
"Returns the background attribute.\n"
"\n"
"This is the highlight used for selectable (but not currently selected)\n"
"menu items.");

#define _CURSES_MENU_MENU_BACK_METHODDEF    \
    {"back", (PyCFunction)_curses_menu_menu_back, METH_NOARGS, _curses_menu_menu_back__doc__},

static PyObject *
_curses_menu_menu_back_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_back(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_back_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_back__doc__,
"set_back($self, /, back)\n"
"--\n"
"\n"
"Set the background attribute.\n"
"\n"
"This is the highlight used for selectable (but not currently selected)\n"
"menu items.");

#define _CURSES_MENU_MENU_SET_BACK_METHODDEF    \
    {"set_back", (PyCFunction)(void(*)(void))_curses_menu_menu_set_back, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_back__doc__},

static PyObject *
_curses_menu_menu_set_back_impl(PyCursesMenuObject *self, unsigned int back);

static PyObject *
_curses_menu_menu_set_back(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"back", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_back", 0};
    PyObject *argsbuf[1];
    unsigned int back;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    back = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (back == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_back_impl(self, back);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_grey__doc__,
"grey($self, /)\n"
"--\n"
"\n"
"Returns the grey attribute.\n"
"\n"
"This is the highlight used for un-selectable menu items in menus that\n"
"permit more than one selection.");

#define _CURSES_MENU_MENU_GREY_METHODDEF    \
    {"grey", (PyCFunction)_curses_menu_menu_grey, METH_NOARGS, _curses_menu_menu_grey__doc__},

static PyObject *
_curses_menu_menu_grey_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_grey(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_grey_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_grey__doc__,
"set_grey($self, /, grey)\n"
"--\n"
"\n"
"Set the grey attribute.\n"
"\n"
"This is the highlight used for un-selectable menu items in menus that\n"
"permit more than one selection.");

#define _CURSES_MENU_MENU_SET_GREY_METHODDEF    \
    {"set_grey", (PyCFunction)(void(*)(void))_curses_menu_menu_set_grey, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_grey__doc__},

static PyObject *
_curses_menu_menu_set_grey_impl(PyCursesMenuObject *self, unsigned int grey);

static PyObject *
_curses_menu_menu_set_grey(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"grey", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_grey", 0};
    PyObject *argsbuf[1];
    unsigned int grey;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    grey = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (grey == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_grey_impl(self, grey);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_pad__doc__,
"pad($self, /)\n"
"--\n"
"\n"
"Returns the pad character.\n"
"\n"
"This is the character used to fill the space between the name and description\n"
"parts of a menu item.");

#define _CURSES_MENU_MENU_PAD_METHODDEF    \
    {"pad", (PyCFunction)_curses_menu_menu_pad, METH_NOARGS, _curses_menu_menu_pad__doc__},

static PyObject *
_curses_menu_menu_pad_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_pad(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_pad_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_pad__doc__,
"set_pad($self, /, pad)\n"
"--\n"
"\n"
"Set the pad character..\n"
"\n"
"This is the character used to fill the space between the name and description\n"
"parts of a menu item.");

#define _CURSES_MENU_MENU_SET_PAD_METHODDEF    \
    {"set_pad", (PyCFunction)(void(*)(void))_curses_menu_menu_set_pad, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_pad__doc__},

static PyObject *
_curses_menu_menu_set_pad_impl(PyCursesMenuObject *self, int pad);

static PyObject *
_curses_menu_menu_set_pad(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"pad", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_pad", 0};
    PyObject *argsbuf[1];
    int pad;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    pad = _PyLong_AsInt(args[0]);
    if (pad == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_pad_impl(self, pad);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_items__doc__,
"items($self, /)\n"
"--\n"
"\n"
"Returns the item of the given menu.");

#define _CURSES_MENU_MENU_ITEMS_METHODDEF    \
    {"items", (PyCFunction)_curses_menu_menu_items, METH_NOARGS, _curses_menu_menu_items__doc__},

static PyObject *
_curses_menu_menu_items_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_items(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_items_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_items__doc__,
"set_items($self, /, items)\n"
"--\n"
"\n"
"Changes the items of the given menu.\n"
"\n"
"  items\n"
"    Tuple with new items");

#define _CURSES_MENU_MENU_SET_ITEMS_METHODDEF    \
    {"set_items", (PyCFunction)(void(*)(void))_curses_menu_menu_set_items, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_items__doc__},

static PyObject *
_curses_menu_menu_set_items_impl(PyCursesMenuObject *self, PyObject *items);

static PyObject *
_curses_menu_menu_set_items(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"items", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_items", 0};
    PyObject *argsbuf[1];
    PyObject *items;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    items = args[0];
    return_value = _curses_menu_menu_set_items_impl(self, items);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_count__doc__,
"count($self, /)\n"
"--\n"
"\n"
"Return the count of items in menu.");

#define _CURSES_MENU_MENU_COUNT_METHODDEF    \
    {"count", (PyCFunction)_curses_menu_menu_count, METH_NOARGS, _curses_menu_menu_count__doc__},

static PyObject *
_curses_menu_menu_count_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_count(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_count_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_userptr__doc__,
"userptr($self, /)\n"
"--\n"
"\n"
"Get the menu user pointer field.\n"
"\n"
"Every menu and every menu item has a field that can be used to hold\n"
"application-specific data (that is, the menu-driver code leaves it\n"
"alone).");

#define _CURSES_MENU_MENU_USERPTR_METHODDEF    \
    {"userptr", (PyCFunction)_curses_menu_menu_userptr, METH_NOARGS, _curses_menu_menu_userptr__doc__},

static PyObject *
_curses_menu_menu_userptr_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_userptr(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_userptr_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_userptr__doc__,
"set_userptr($self, /, obj)\n"
"--\n"
"\n"
"Set the menu user pointer field.\n"
"\n"
"Every menu and every menu item has a field that can be used to hold\n"
"application-specific data (that is, the menu-driver code leaves it\n"
"alone).");

#define _CURSES_MENU_MENU_SET_USERPTR_METHODDEF    \
    {"set_userptr", (PyCFunction)(void(*)(void))_curses_menu_menu_set_userptr, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_userptr__doc__},

static PyObject *
_curses_menu_menu_set_userptr_impl(PyCursesMenuObject *self, PyObject *obj);

static PyObject *
_curses_menu_menu_set_userptr(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"obj", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_userptr", 0};
    PyObject *argsbuf[1];
    PyObject *obj;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    obj = args[0];
    return_value = _curses_menu_menu_set_userptr_impl(self, obj);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_mark__doc__,
"mark($self, /)\n"
"--\n"
"\n"
"Get the menu mark string.\n"
"\n"
"In order to make menu selections visible on older terminals without\n"
"highlighting or color capability, the menu library marks selected items\n"
"in a menu with a prefix string.");

#define _CURSES_MENU_MENU_MARK_METHODDEF    \
    {"mark", (PyCFunction)_curses_menu_menu_mark, METH_NOARGS, _curses_menu_menu_mark__doc__},

static PyObject *
_curses_menu_menu_mark_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_mark(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_mark_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_mark__doc__,
"set_mark($self, /, obj)\n"
"--\n"
"\n"
"Set the menu mark string.\n"
"\n"
"In order to make menu selections visible on older terminals without\n"
"highlighting or color capability, the menu library marks selected items\n"
"in a menu with a prefix string.\n"
"\n"
"Calling set_mark with None will abolish the mark\n"
"string. Note that changing the length of the mark string for a menu\n"
"while the menu is posted is likely to produce unhelpful behavior.");

#define _CURSES_MENU_MENU_SET_MARK_METHODDEF    \
    {"set_mark", (PyCFunction)(void(*)(void))_curses_menu_menu_set_mark, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_mark__doc__},

static PyObject *
_curses_menu_menu_set_mark_impl(PyCursesMenuObject *self, PyObject *obj);

static PyObject *
_curses_menu_menu_set_mark(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"obj", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_mark", 0};
    PyObject *argsbuf[1];
    PyObject *obj;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    obj = args[0];
    return_value = _curses_menu_menu_set_mark_impl(self, obj);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_current_item__doc__,
"current_item($self, /)\n"
"--\n"
"\n"
"Get the current item (the item on which the menu cursor is positioned)\n"
"\n"
"Return None, if no current item is selected.");

#define _CURSES_MENU_MENU_CURRENT_ITEM_METHODDEF    \
    {"current_item", (PyCFunction)_curses_menu_menu_current_item, METH_NOARGS, _curses_menu_menu_current_item__doc__},

static PyObject *
_curses_menu_menu_current_item_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_current_item(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_current_item_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_current_item__doc__,
"set_current_item($self, /, item)\n"
"--\n"
"\n"
"Set the current item (the item on which the menu cursor is positioned)\n"
"\n"
"  item\n"
"    curses item object");

#define _CURSES_MENU_MENU_SET_CURRENT_ITEM_METHODDEF    \
    {"set_current_item", (PyCFunction)(void(*)(void))_curses_menu_menu_set_current_item, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_current_item__doc__},

static PyObject *
_curses_menu_menu_set_current_item_impl(PyCursesMenuObject *self,
                                        PyObject *item);

static PyObject *
_curses_menu_menu_set_current_item(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"item", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_current_item", 0};
    PyObject *argsbuf[1];
    PyObject *item;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    item = args[0];
    return_value = _curses_menu_menu_set_current_item_impl(self, item);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_top_row__doc__,
"top_row($self, /)\n"
"--\n"
"\n"
"Get the index of the top menu row being displayed.");

#define _CURSES_MENU_MENU_TOP_ROW_METHODDEF    \
    {"top_row", (PyCFunction)_curses_menu_menu_top_row, METH_NOARGS, _curses_menu_menu_top_row__doc__},

static PyObject *
_curses_menu_menu_top_row_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_top_row(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_top_row_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_top_row__doc__,
"set_top_row($self, /, row)\n"
"--\n"
"\n"
"Set the index of the top menu row being displayed.");

#define _CURSES_MENU_MENU_SET_TOP_ROW_METHODDEF    \
    {"set_top_row", (PyCFunction)(void(*)(void))_curses_menu_menu_set_top_row, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_top_row__doc__},

static PyObject *
_curses_menu_menu_set_top_row_impl(PyCursesMenuObject *self, int row);

static PyObject *
_curses_menu_menu_set_top_row(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"row", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_top_row", 0};
    PyObject *argsbuf[1];
    int row;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    row = _PyLong_AsInt(args[0]);
    if (row == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_top_row_impl(self, row);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_format__doc__,
"format($self, /)\n"
"--\n"
"\n"
"Get the maximum display size.");

#define _CURSES_MENU_MENU_FORMAT_METHODDEF    \
    {"format", (PyCFunction)_curses_menu_menu_format, METH_NOARGS, _curses_menu_menu_format__doc__},

static PyObject *
_curses_menu_menu_format_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_format(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_format_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_format__doc__,
"set_format($self, /, rows, cols)\n"
"--\n"
"\n"
"Set the maximum display size.\n"
"\n"
"If this size is too small to display all menu items,\n"
"the menu will be made scrollable.");

#define _CURSES_MENU_MENU_SET_FORMAT_METHODDEF    \
    {"set_format", (PyCFunction)(void(*)(void))_curses_menu_menu_set_format, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_format__doc__},

static PyObject *
_curses_menu_menu_set_format_impl(PyCursesMenuObject *self, int rows,
                                  int cols);

static PyObject *
_curses_menu_menu_set_format(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"rows", "cols", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_format", 0};
    PyObject *argsbuf[2];
    int rows;
    int cols;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 2, 2, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    rows = _PyLong_AsInt(args[0]);
    if (rows == -1 && PyErr_Occurred()) {
        goto exit;
    }
    cols = _PyLong_AsInt(args[1]);
    if (cols == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_format_impl(self, rows, cols);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_spacing__doc__,
"spacing($self, /)\n"
"--\n"
"\n"
"Get the spacing information for the menu.");

#define _CURSES_MENU_MENU_SPACING_METHODDEF    \
    {"spacing", (PyCFunction)_curses_menu_menu_spacing, METH_NOARGS, _curses_menu_menu_spacing__doc__},

static PyObject *
_curses_menu_menu_spacing_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_spacing(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_spacing_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_spacing__doc__,
"set_spacing($self, /, description, rows, cols)\n"
"--\n"
"\n"
"Set the spacing information for the menu.\n"
"\n"
"  description\n"
"    number of spaces between an item name and an item description\n"
"  rows\n"
"    number of rows that are used for an item.\n"
"  cols\n"
"    number of blanks between columns of items\n"
"\n"
"If this size is too small to display all menu items,\n"
"the menu will be made scrollable.");

#define _CURSES_MENU_MENU_SET_SPACING_METHODDEF    \
    {"set_spacing", (PyCFunction)(void(*)(void))_curses_menu_menu_set_spacing, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_spacing__doc__},

static PyObject *
_curses_menu_menu_set_spacing_impl(PyCursesMenuObject *self, int description,
                                   int rows, int cols);

static PyObject *
_curses_menu_menu_set_spacing(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"description", "rows", "cols", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_spacing", 0};
    PyObject *argsbuf[3];
    int description;
    int rows;
    int cols;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 3, 3, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    description = _PyLong_AsInt(args[0]);
    if (description == -1 && PyErr_Occurred()) {
        goto exit;
    }
    rows = _PyLong_AsInt(args[1]);
    if (rows == -1 && PyErr_Occurred()) {
        goto exit;
    }
    cols = _PyLong_AsInt(args[2]);
    if (cols == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_spacing_impl(self, description, rows, cols);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_post__doc__,
"post($self, /)\n"
"--\n"
"\n"
"Displays the menu to its associated subwindow.\n"
"\n"
"To trigger physical display of the subwindow,use refresh or some\n"
"equivalent curses routine (the implicit doupdate triggered by an curses\n"
"input request will do). post resets the selection status of all\n"
"items.");

#define _CURSES_MENU_MENU_POST_METHODDEF    \
    {"post", (PyCFunction)_curses_menu_menu_post, METH_NOARGS, _curses_menu_menu_post__doc__},

static PyObject *
_curses_menu_menu_post_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_post(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_post_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_unpost__doc__,
"unpost($self, /)\n"
"--\n"
"\n"
"Erases the menu from its associated subwindow.");

#define _CURSES_MENU_MENU_UNPOST_METHODDEF    \
    {"unpost", (PyCFunction)_curses_menu_menu_unpost, METH_NOARGS, _curses_menu_menu_unpost__doc__},

static PyObject *
_curses_menu_menu_unpost_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_unpost(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_unpost_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_pattern__doc__,
"pattern($self, /)\n"
"--\n"
"\n"
"Get the pattern buffer.\n"
"\n"
"Every menu has an associated pattern match buffer. As input events\n"
"that are printable characters come in, they are appended to this match\n"
"buffer and tested for a match,");

#define _CURSES_MENU_MENU_PATTERN_METHODDEF    \
    {"pattern", (PyCFunction)_curses_menu_menu_pattern, METH_NOARGS, _curses_menu_menu_pattern__doc__},

static PyObject *
_curses_menu_menu_pattern_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_pattern(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_pattern_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_pattern__doc__,
"set_pattern($self, /, pattern)\n"
"--\n"
"\n"
"Sets the pattern buffer and try to find the first matching item.\n"
"\n"
"Every menu has an associated pattern match buffer. As input events\n"
"that are printable characters come in, they are appended to this match\n"
"buffer and tested for a match,");

#define _CURSES_MENU_MENU_SET_PATTERN_METHODDEF    \
    {"set_pattern", (PyCFunction)(void(*)(void))_curses_menu_menu_set_pattern, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_pattern__doc__},

static PyObject *
_curses_menu_menu_set_pattern_impl(PyCursesMenuObject *self,
                                   PyObject *pattern);

static PyObject *
_curses_menu_menu_set_pattern(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"pattern", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_pattern", 0};
    PyObject *argsbuf[1];
    PyObject *pattern;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    pattern = args[0];
    return_value = _curses_menu_menu_set_pattern_impl(self, pattern);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_driver__doc__,
"driver($self, /, c)\n"
"--\n"
"\n"
"Funnel input events to the menu.");

#define _CURSES_MENU_MENU_DRIVER_METHODDEF    \
    {"driver", (PyCFunction)(void(*)(void))_curses_menu_menu_driver, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_driver__doc__},

static PyObject *
_curses_menu_menu_driver_impl(PyCursesMenuObject *self, int c);

static PyObject *
_curses_menu_menu_driver(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"c", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "driver", 0};
    PyObject *argsbuf[1];
    int c;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    c = _PyLong_AsInt(args[0]);
    if (c == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_driver_impl(self, c);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_set_opts__doc__,
"set_opts($self, /, opts)\n"
"--\n"
"\n"
"Set all the given menu\'s option bits.");

#define _CURSES_MENU_MENU_SET_OPTS_METHODDEF    \
    {"set_opts", (PyCFunction)(void(*)(void))_curses_menu_menu_set_opts, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_opts__doc__},

static PyObject *
_curses_menu_menu_set_opts_impl(PyCursesMenuObject *self, unsigned int opts);

static PyObject *
_curses_menu_menu_set_opts(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"opts", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_opts", 0};
    PyObject *argsbuf[1];
    unsigned int opts;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    opts = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (opts == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_set_opts_impl(self, opts);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_opts_on__doc__,
"opts_on($self, /, opts)\n"
"--\n"
"\n"
"Turns on the given option bits, and leave others alone.");

#define _CURSES_MENU_MENU_OPTS_ON_METHODDEF    \
    {"opts_on", (PyCFunction)(void(*)(void))_curses_menu_menu_opts_on, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_opts_on__doc__},

static PyObject *
_curses_menu_menu_opts_on_impl(PyCursesMenuObject *self, unsigned int opts);

static PyObject *
_curses_menu_menu_opts_on(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"opts", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "opts_on", 0};
    PyObject *argsbuf[1];
    unsigned int opts;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    opts = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (opts == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_opts_on_impl(self, opts);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_opts_off__doc__,
"opts_off($self, /, opts)\n"
"--\n"
"\n"
"Turn off the given option bits, and leave others alone.");

#define _CURSES_MENU_MENU_OPTS_OFF_METHODDEF    \
    {"opts_off", (PyCFunction)(void(*)(void))_curses_menu_menu_opts_off, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_opts_off__doc__},

static PyObject *
_curses_menu_menu_opts_off_impl(PyCursesMenuObject *self, unsigned int opts);

static PyObject *
_curses_menu_menu_opts_off(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"opts", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "opts_off", 0};
    PyObject *argsbuf[1];
    unsigned int opts;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    opts = (unsigned int)PyLong_AsUnsignedLongMask(args[0]);
    if (opts == (unsigned int)-1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_menu_opts_off_impl(self, opts);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_opts__doc__,
"opts($self, /)\n"
"--\n"
"\n"
"Returns the menu\'s current option bits");

#define _CURSES_MENU_MENU_OPTS_METHODDEF    \
    {"opts", (PyCFunction)_curses_menu_menu_opts, METH_NOARGS, _curses_menu_menu_opts__doc__},

static PyObject *
_curses_menu_menu_opts_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_opts(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_opts_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_item_init__doc__,
"set_item_init($self, /, func)\n"
"--\n"
"\n"
"Set hook to be called at menu-post time and each time the selected item changes.");

#define _CURSES_MENU_MENU_SET_ITEM_INIT_METHODDEF    \
    {"set_item_init", (PyCFunction)(void(*)(void))_curses_menu_menu_set_item_init, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_item_init__doc__},

static PyObject *
_curses_menu_menu_set_item_init_impl(PyCursesMenuObject *self,
                                     PyObject *func);

static PyObject *
_curses_menu_menu_set_item_init(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"func", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_item_init", 0};
    PyObject *argsbuf[1];
    PyObject *func;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    func = args[0];
    return_value = _curses_menu_menu_set_item_init_impl(self, func);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_item_init__doc__,
"item_init($self, /)\n"
"--\n"
"\n"
"Get hook to be called at menu-post time and each time the selected item changes.");

#define _CURSES_MENU_MENU_ITEM_INIT_METHODDEF    \
    {"item_init", (PyCFunction)_curses_menu_menu_item_init, METH_NOARGS, _curses_menu_menu_item_init__doc__},

static PyObject *
_curses_menu_menu_item_init_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_item_init(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_item_init_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_item_term__doc__,
"set_item_term($self, /, func)\n"
"--\n"
"\n"
"Set hook to be called at menu-unpost time and each time the selected item changes (before the change).");

#define _CURSES_MENU_MENU_SET_ITEM_TERM_METHODDEF    \
    {"set_item_term", (PyCFunction)(void(*)(void))_curses_menu_menu_set_item_term, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_item_term__doc__},

static PyObject *
_curses_menu_menu_set_item_term_impl(PyCursesMenuObject *self,
                                     PyObject *func);

static PyObject *
_curses_menu_menu_set_item_term(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"func", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_item_term", 0};
    PyObject *argsbuf[1];
    PyObject *func;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    func = args[0];
    return_value = _curses_menu_menu_set_item_term_impl(self, func);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_item_term__doc__,
"item_term($self, /)\n"
"--\n"
"\n"
"Get hook to be called at menu-unpost time and each time the selected item changes (before the change).");

#define _CURSES_MENU_MENU_ITEM_TERM_METHODDEF    \
    {"item_term", (PyCFunction)_curses_menu_menu_item_term, METH_NOARGS, _curses_menu_menu_item_term__doc__},

static PyObject *
_curses_menu_menu_item_term_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_item_term(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_item_term_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_menu_init__doc__,
"set_menu_init($self, /, func)\n"
"--\n"
"\n"
"Set hook to be called at menu-post time and just after the top row on the menu changes once it is posted.");

#define _CURSES_MENU_MENU_SET_MENU_INIT_METHODDEF    \
    {"set_menu_init", (PyCFunction)(void(*)(void))_curses_menu_menu_set_menu_init, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_menu_init__doc__},

static PyObject *
_curses_menu_menu_set_menu_init_impl(PyCursesMenuObject *self,
                                     PyObject *func);

static PyObject *
_curses_menu_menu_set_menu_init(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"func", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_menu_init", 0};
    PyObject *argsbuf[1];
    PyObject *func;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    func = args[0];
    return_value = _curses_menu_menu_set_menu_init_impl(self, func);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_menu_init__doc__,
"menu_init($self, /)\n"
"--\n"
"\n"
"Get hook to be called at menu-post time and just after the top row on the menu changes once it is posted.");

#define _CURSES_MENU_MENU_MENU_INIT_METHODDEF    \
    {"menu_init", (PyCFunction)_curses_menu_menu_menu_init, METH_NOARGS, _curses_menu_menu_menu_init__doc__},

static PyObject *
_curses_menu_menu_menu_init_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_menu_init(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_menu_init_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_menu_term__doc__,
"set_menu_term($self, /, func)\n"
"--\n"
"\n"
"Set hook to be called at menu-unpost time and just before the top row on the menu changes once it is posted.");

#define _CURSES_MENU_MENU_SET_MENU_TERM_METHODDEF    \
    {"set_menu_term", (PyCFunction)(void(*)(void))_curses_menu_menu_set_menu_term, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_menu_term__doc__},

static PyObject *
_curses_menu_menu_set_menu_term_impl(PyCursesMenuObject *self,
                                     PyObject *func);

static PyObject *
_curses_menu_menu_set_menu_term(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"func", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_menu_term", 0};
    PyObject *argsbuf[1];
    PyObject *func;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    func = args[0];
    return_value = _curses_menu_menu_set_menu_term_impl(self, func);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_menu_term__doc__,
"menu_term($self, /)\n"
"--\n"
"\n"
"Get hook to be called at menu-unpost time and just before the top row on the menu changes once it is posted.");

#define _CURSES_MENU_MENU_MENU_TERM_METHODDEF    \
    {"menu_term", (PyCFunction)_curses_menu_menu_menu_term, METH_NOARGS, _curses_menu_menu_menu_term__doc__},

static PyObject *
_curses_menu_menu_menu_term_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_menu_term(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_menu_term_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_pos_cursor__doc__,
"pos_cursor($self, /)\n"
"--\n"
"\n"
"Restore the cursor to the current position associated with the menu\'s selected item.\n"
"\n"
"This is useful after curses routines have been called to do screen-painting in response to a\n"
"menu select.");

#define _CURSES_MENU_MENU_POS_CURSOR_METHODDEF    \
    {"pos_cursor", (PyCFunction)_curses_menu_menu_pos_cursor, METH_NOARGS, _curses_menu_menu_pos_cursor__doc__},

static PyObject *
_curses_menu_menu_pos_cursor_impl(PyCursesMenuObject *self);

static PyObject *
_curses_menu_menu_pos_cursor(PyCursesMenuObject *self, PyObject *Py_UNUSED(ignored))
{
    return _curses_menu_menu_pos_cursor_impl(self);
}

PyDoc_STRVAR(_curses_menu_menu_set_win__doc__,
"set_win($self, /, win)\n"
"--\n"
"\n"
"Set menu window.\n"
"\n"
"Every menu has an associated pair of curses windows. The menu window\n"
"displays any title and border associated with the window; the menu sub-\n"
"window displays the items of the menu that are currently available for\n"
"selection.");

#define _CURSES_MENU_MENU_SET_WIN_METHODDEF    \
    {"set_win", (PyCFunction)(void(*)(void))_curses_menu_menu_set_win, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_win__doc__},

static PyObject *
_curses_menu_menu_set_win_impl(PyCursesMenuObject *self, PyObject *win);

static PyObject *
_curses_menu_menu_set_win(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"win", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_win", 0};
    PyObject *argsbuf[1];
    PyObject *win;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    win = args[0];
    return_value = _curses_menu_menu_set_win_impl(self, win);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_menu_set_sub__doc__,
"set_sub($self, /, win)\n"
"--\n"
"\n"
"Set sub window.\n"
"\n"
"Every menu has an associated pair of curses windows. The menu window\n"
"displays any title and border associated with the window; the menu sub-\n"
"window displays the items of the menu that are currently available for\n"
"selection.");

#define _CURSES_MENU_MENU_SET_SUB_METHODDEF    \
    {"set_sub", (PyCFunction)(void(*)(void))_curses_menu_menu_set_sub, METH_FASTCALL|METH_KEYWORDS, _curses_menu_menu_set_sub__doc__},

static PyObject *
_curses_menu_menu_set_sub_impl(PyCursesMenuObject *self, PyObject *win);

static PyObject *
_curses_menu_menu_set_sub(PyCursesMenuObject *self, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"win", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "set_sub", 0};
    PyObject *argsbuf[1];
    PyObject *win;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    win = args[0];
    return_value = _curses_menu_menu_set_sub_impl(self, win);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_new_item__doc__,
"new_item($module, /, name, description=<unrepresentable>)\n"
"--\n"
"\n"
"Create a new item and initialize it from name and description.\n"
"\n"
"  name\n"
"    Name.\n"
"  description\n"
"    Description.");

#define _CURSES_MENU_NEW_ITEM_METHODDEF    \
    {"new_item", (PyCFunction)(void(*)(void))_curses_menu_new_item, METH_FASTCALL|METH_KEYWORDS, _curses_menu_new_item__doc__},

static PyObject *
_curses_menu_new_item_impl(PyObject *module, PyObject *name,
                           PyObject *description);

static PyObject *
_curses_menu_new_item(PyObject *module, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"name", "description", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "new_item", 0};
    PyObject *argsbuf[2];
    Py_ssize_t noptargs = nargs + (kwnames ? PyTuple_GET_SIZE(kwnames) : 0) - 1;
    PyObject *name;
    PyObject *description = NULL;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 2, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    name = args[0];
    if (!noptargs) {
        goto skip_optional_pos;
    }
    description = args[1];
skip_optional_pos:
    return_value = _curses_menu_new_item_impl(module, name, description);

exit:
    return return_value;
}

PyDoc_STRVAR(_curses_menu_new_menu__doc__,
"new_menu($module, /, items)\n"
"--\n"
"\n"
"Create a new menu connected to the specified items.\n"
"\n"
"  items\n"
"    Tuple with items");

#define _CURSES_MENU_NEW_MENU_METHODDEF    \
    {"new_menu", (PyCFunction)(void(*)(void))_curses_menu_new_menu, METH_FASTCALL|METH_KEYWORDS, _curses_menu_new_menu__doc__},

static PyObject *
_curses_menu_new_menu_impl(PyObject *module, PyObject *items);

static PyObject *
_curses_menu_new_menu(PyObject *module, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"items", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "new_menu", 0};
    PyObject *argsbuf[1];
    PyObject *items;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    items = args[0];
    return_value = _curses_menu_new_menu_impl(module, items);

exit:
    return return_value;
}

#if defined(NCURSES_VERSION)

PyDoc_STRVAR(_curses_menu_request_name__doc__,
"request_name($module, /, request)\n"
"--\n"
"\n"
"Returns the printable name of a menu request code.");

#define _CURSES_MENU_REQUEST_NAME_METHODDEF    \
    {"request_name", (PyCFunction)(void(*)(void))_curses_menu_request_name, METH_FASTCALL|METH_KEYWORDS, _curses_menu_request_name__doc__},

static PyObject *
_curses_menu_request_name_impl(PyObject *module, int request);

static PyObject *
_curses_menu_request_name(PyObject *module, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"request", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "request_name", 0};
    PyObject *argsbuf[1];
    int request;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    request = _PyLong_AsInt(args[0]);
    if (request == -1 && PyErr_Occurred()) {
        goto exit;
    }
    return_value = _curses_menu_request_name_impl(module, request);

exit:
    return return_value;
}

#endif /* defined(NCURSES_VERSION) */

#if defined(NCURSES_VERSION)

PyDoc_STRVAR(_curses_menu_request_by_name__doc__,
"request_by_name($module, /, name)\n"
"--\n"
"\n"
"Searches in the name-table for a request with the given name and return its request code.");

#define _CURSES_MENU_REQUEST_BY_NAME_METHODDEF    \
    {"request_by_name", (PyCFunction)(void(*)(void))_curses_menu_request_by_name, METH_FASTCALL|METH_KEYWORDS, _curses_menu_request_by_name__doc__},

static PyObject *
_curses_menu_request_by_name_impl(PyObject *module, const char *name);

static PyObject *
_curses_menu_request_by_name(PyObject *module, PyObject *const *args, Py_ssize_t nargs, PyObject *kwnames)
{
    PyObject *return_value = NULL;
    static const char * const _keywords[] = {"name", NULL};
    static _PyArg_Parser _parser = {NULL, _keywords, "request_by_name", 0};
    PyObject *argsbuf[1];
    const char *name;

    args = _PyArg_UnpackKeywords(args, nargs, NULL, kwnames, &_parser, 1, 1, 0, argsbuf);
    if (!args) {
        goto exit;
    }
    if (!PyUnicode_Check(args[0])) {
        _PyArg_BadArgument("request_by_name", "argument 'name'", "str", args[0]);
        goto exit;
    }
    Py_ssize_t name_length;
    name = PyUnicode_AsUTF8AndSize(args[0], &name_length);
    if (name == NULL) {
        goto exit;
    }
    if (strlen(name) != (size_t)name_length) {
        PyErr_SetString(PyExc_ValueError, "embedded null character");
        goto exit;
    }
    return_value = _curses_menu_request_by_name_impl(module, name);

exit:
    return return_value;
}

#endif /* defined(NCURSES_VERSION) */

#ifndef _CURSES_MENU_REQUEST_NAME_METHODDEF
    #define _CURSES_MENU_REQUEST_NAME_METHODDEF
#endif /* !defined(_CURSES_MENU_REQUEST_NAME_METHODDEF) */

#ifndef _CURSES_MENU_REQUEST_BY_NAME_METHODDEF
    #define _CURSES_MENU_REQUEST_BY_NAME_METHODDEF
#endif /* !defined(_CURSES_MENU_REQUEST_BY_NAME_METHODDEF) */
/*[clinic end generated code: output=498f04d8af6e2391 input=a9049054013a1b77]*/
