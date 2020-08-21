:mod:`curses.menu` --- A menu extension for curses
==================================================

.. module:: curses.menu
   :synopsis: A curses extension that adds menu boxes to curses.
.. sectionauthor:: Ben Trofatter <bentrofatter@gmail.com>


Menu description.

The :mod:`curses.menu` module provides an interface to the curses menu
extension library.


.. _cursesmenu-functions:

Functions
---------

The module :mod:`curses.menu` defines the following functions:


.. function:: new_item(name[, description=None])

   Return an item object.


.. function:: new_menu(items)

   Return a menu object associated with the given items.  By default, the
   menu will be tied to the ``stdscr``, but this can be overridden globally
   using :func:`set_menu_win` and :func:`set_menu_sub` or on a per-menu
   basis with :meth:`win` and :meth:`sub` as described below.


.. function:: set_menu_win(win)

   Set the default window used to display the title and border of subsequently
   created menus.


.. function:: set_menu_win(win)

   Set the default window used to display the items of subsequently created
   menus.


.. function:: set_menu_mark(mark)

   Set the default menu mark string. This can be overridden with
   :meth:`set_mark` as described below.


.. function:: request_by_name(request)

   Return the printable name of a menu request code.
   

.. function:: request_name(name)

   Return the menu request code associated with the given name.


.. _curses-menu-item-objects:

Item Objects
------------

Item objects, as returned by :func:`new_item` above, have the following
methods:


.. method:: Item.description()

   Return the description string of the item if it is set else ``None``.


.. method:: Item.index()

   Return the index of the item in its menu's item list.


.. method:: Item.name()

   Return the name string of the item.


.. method:: Item.opts()

   Return the item's currently set option bits.  Currently, there is only one
   defined item option, :const:`O_SELECTABLE`, which when set allows the item to
   be selected from its menu.  This option is on by default.


.. method:: Item.opts_off(opts)

   Turn off the given, logically-OR'ed option bits, leaving the rest alone.

   
.. method:: Item.opts_on()

   Turn on the given, logically-OR'ed option bits, leaving the rest alone.


.. method:: Item.set_opts(opts)

   Set the item's options bits by logically-OR'ing options together. Currently,
   there is only one defined item option, :const:`O_SELECTABLE`, which when set 
   allows the item to be selected from its menu.  This option is on by default.
   

.. method:: Item.set_userptr(obj)

   Set the item's user point to `obj`. This is used to associate an arbitrary
   piece of data with the item, and can be any Python object. 


.. method:: Item.set_value(selected)

   In a multi-valued menu, you can select or deselect the item by passing
   ``True`` or ``False``, respectively.


.. method:: Item.userptr()

   Return the user pointer for the item.


.. method:: Item.value()

   In a multi-valued menu, returns ``True`` if the item is currently selected
   or ``False`` if it isn't.


.. method:: Item.visible()

   Return ``True`` if the item is currently mapped onto the screen or
   ``False`` if it is not.


.. _curses-menu-menu-objects:

Menu Objects
------------

Menu objects, as returned by :func:`new_menu` above, have the following
methods:


.. method:: Menu.back()

   Return the background attribute.  This is the highlight used for selectable
   menu items that are not currently selected.  The default is
   :const:`curses.A_NORMAL`.


.. method:: Menu.current_item()

   Return the currently active menu item.


.. method:: Menu.driver(c)

   Once the menu has been posted, user input should be passed to
   :meth:`driver`.  This routine has three major input cases:

   Menu navigation requests
      See :ref:`curses-menu-requests` for available values and their meanings.

   Printable characters
      The character is appended to the pattern buffer. If the buffer does not
      match any items in the menu, the character is subsequently removed.

   A :const:`KEY_MOUSE` request associated with a mouse event
      The driver translates the click event into one of the previously
      mentioned menu navigation requests.

      If you click above the display region of the menu:

      +--------------+-------------------------+
      | Mouse Event  | Menu Navigation Request |
      +==============+=========================+
      | Single Click | :const:`REQ_SCR_ULINE`  |
      +--------------+-------------------------+
      | Double Click | :const:`REQ_SCR_UPAGE`  |
      +--------------+-------------------------+
      | Triple Click | :const:`REQ_FIRST_ITEM` |
      +--------------+-------------------------+

      If you click below the display region of the menu:

      +--------------+-------------------------+
      | Mouse Event  | Menu Navigation Request |
      +==============+=========================+
      | Single Click | :const:`REQ_SCR_DLINE`  |
      +--------------+-------------------------+
      | Double Click | :const:`REQ_SCR_DPAGE`  |
      +--------------+-------------------------+
      | Triple Click | :const:`REQ_LAST_ITEM`  |
      +--------------+-------------------------+

      If you click an item within the display area of the menu:

      +--------------+------------------------------------------------------+
      | Mouse Event  | Action Taken                                         |
      +==============+======================================================+
      | Single Click | Menu cursor is positioned on that item.              |
      +--------------+------------------------------------------------------+ 
      | Double Click | :const:`REQ_TOGGLE_ITEM` is generated and the driver |
      |              | returns an error state intended to indicate that an  |
      |              | item specific, custom command should be sent to the  |
      |              | driver.                                              |
      +--------------+------------------------------------------------------+


.. method:: Menu.fore()

   Return the foreground attribute.  This is the highlight used for selected
   menu items.  The default is :const:`curses.A_REVERSE`.


.. method:: Menu.format()

   Return the maximum-size constraints for the given menu as a 2-tuple of
   ``(rows, columns)``.


.. method:: Menu.grey()

   Return the grey attribute of menu.  This is the highlight used for 
   un-selectable menu items in menus that permit more than one selection. The
   default is :const:`curses.A_UNDERLINE`.


.. method:: Menu.item_count()

   Return the number of items associated with the menu.


.. method:: Menu.item_init()

   Return the currently set item init hook if one exists, otherwise ``None``.
   The item init hook is a Python callable object that takes a menu as its
   only argument. It is called at menu post time and immediately after the
   selected item changes.


.. method:: Menu.item_term()

   Return the currently set item term hook if one exists, otherwise ``None``.
   The item term hook is a Python callable object that takes a menu as its
   only argument. It is called at menu unpost time and immediately before the
   selected item changes.


.. method:: Menu.items()

   Return a tuple of the items currently associated with the menu.


.. method:: Menu.mark()

   Return the string used to mark a menu item as selected.  Defaults to "-".


.. method:: Menu.menu_init()

   Return the currently set menu init hook if one exists, otherwise ``None``.
   The menu init hook is a Python callable object that takes a menu as its
   only argument. It is called at menu post time and immediately after the
   top row of the menu changes once it is posted.


.. method:: Menu.menu_term()

   Return the currently set menu term hook if one exists, otherwise ``None``.
   The menu term hook is a Python callable object that takes a menu as its
   only argument. It is called at menu unpost time and immediately before the
   top row of the menu changes once it is posted.


.. method:: Menu.opts()

   Return the menu's currently set option bits. See below for a description
   of menu options. See :ref:`curses-menu-menu-options` for a listing of
   available options and their meanings.


.. method:: Menu.opts_off(opts)

   Turn off the given, logically-OR'ed option bits, leaving the rest alone.
   See :ref:`curses-menu-menu-options` for a listing of available options
   and their meanings.


.. method:: Menu.opts_on(opts)

   Turn on the given, logically-OR'ed option bits, leaving the rest alone.
   See :ref:`curses-menu-menu-options` for a listing of available options
   and their meanings.


.. method:: Menu.pad()

   Return the currently set pad character. This character appears centered
   between an item's name and its description. The default is " ".


.. method:: Menu.pattern()

   Return the contents of the menu's pattern buffer. Input events that are
   printable characters are appended to this buffer and used to search for
   a matching item.


.. method:: Menu.pos_cursor()

   Restore the cursor to the position currently associated with the menu's
   selected item. Intended to be used after other curses routings have been
   called to do screen-painting in response to a menu select.


.. method:: Menu.post()

   Write the menu to its associated window buffer without actually painting
   the window on the scresn.  To display the menu, call :meth:`refresh` or its
   equivalent on the menu's associated window object (e.g. the implicit
   :func:`doupdate` triggered by a curses input request). :meth:`post` will
   also reset the selection status of all menu items.


.. method:: Menu.scale()

   Return a 2-tuple ``(rows, columns)`` indicating the minimum size required
   for the subwindow of the menu.


.. method:: Menu.set_back(attr)

   Sets the background attribute.  This is the highlight used for selectable
   menu items that are not currently selected.  The default is
   :const:`curses.A_NORMAL`.


.. method:: Menu.set_current_item(item)

   Sets the currently active item (the item on which the menu cursor is
   positioned). The `item` argument must currently be associated with the
   menu.


.. method:: Menu.set_fore(attr)

   Sets the foreground attribute.  This is the highlight used for selected
   menu items.  The default is :const:`curses.A_REVERSE`.


.. method:: Menu.set_format(rows, columns)

   Set the maximum display size of the given menu. If this is too small to
   display all menu items, the menu will be made scrollable. If this size is
   larger than the menu's subwindow and the subwindow is too small to display
   all of the menu's items, :meth:`post` will fail.  The default is 16 rows
   and 1 column. A 0 value for `rows` or `columns` is interpreted as a request
   not to change the current value.


.. method:: Menu.set_grey(attr)

   Sets the grey attribute of menu.  This is the highlight used for 
   un-selectable menu items in menus that permit more than one selection. The
   default is :const:`curses.A_UNDERLINE`.


.. method:: Menu.set_item_init(callback)

   Set the item init hook. The item init hook is called at menu post time and
   immediately after the selected item changes. `callback` is a callable object
   that takes a menu as its only argument.


.. method:: Menu.set_item_term(callback)

   Set the item term hook. The item term hook is called at menu unpost time
   and immediately before the selected item changes. `callback` is a callable
   object that takes a menu as its only argument.


.. method:: Menu.set_items(items)

   Change the list of items associated with the menu.


.. method:: Menu.set_mark(mark)

   Set the string used to mark a menu item as selected. This string will 
   display as a prefix to the item. Changing the length of the menu mark while
   the menu is posted can lead to unexpected behavior.


.. method:: Menu.set_menu_init(callback)

   Set the menu init hook. The menu init hook is called at menu post time and
   immediately after the selected item changes. `callback` is a callable object
   that takes a menu as its only argument.


.. method:: Menu.set_menu_term(callback)

   Set the menu term hook. The menu term hook is called at menu unpost time
   and immediately before the selected item changes. `callback` is a callable
   object that takes a menu as its only argument.


.. method:: Menu.set_opts(opts)

   Set the menu's options bits by logically-OR'ing options together.
   See :ref:`curses-menu-menu-options` for a listing of available options
   and their meanings.


.. method:: Menu.set_pad(pad)

   Set the menu's pad character. This character is centered between an item's
   name and its description. The default is " ".


.. method:: Menu.set_pattern(pattern)

   Attempt to set the menu's pattern buffer. If `pattern` matches one or more
   items, the pattern buffer will be set.


.. method:: Menu.set_spacing(spc_description, spc_rows, spc_columns)

   Set the spacing between menu items. `spc_description` is the number of
   spaces between an item name and its description. It must not be larger
   than :const:`TABSIZE`. The menu system inserts the value of :meth:`pad`
   in the middle of this spacing area and fills the remaining parts with spaces.
   `spc_rows` is the number of rows used for each item. It must not be
   larger than 3. `spc_columns` is the number of blanks between columns
   of items. It must not be larger than :const:`TABSIZE`. Passing 0 for all 
   arguments results in the spacing being reset to the defaults, which is
   1 for each them.


.. method:: Menu.set_sub([win])

   Set the subwindow used to display the items the are currently visible and
   available for selection. Defaults to the ``stdscr``. If no `win` argument
   is passed, the menu's subwindow will be reset to the ``stdscr``.


.. method:: Menu.set_top_row(row)

   Set the number of the row to be displayed at the top of the menu's window.
   This is initially set to 0 and is reset to this value whenever the 
   :const:`O_ROWMAJOR` option is toggled.  The leftmost item on the given row
   then becomes the current item.


.. method:: Menu.set_userptr(obj)

   Set the menu's user point to `obj`. This is used to associate an arbitrary
   piece of data with the menu, and can be any Python object. 


.. method:: Menu.set_win([win])

   Set the window used to display the title and/or border of the menu, should
   they exist. Defaults to the ``stdscr``. If no `win` argument is passed, the
   menu's main window will be reset to the ``stdscr``.


.. method:: Menu.sub()

   Return the menu's subwindow, which is used to display the items of the menu
   that are currently visible and available for selection. This defaults to the
   ``stdscr``. 


.. method:: Menu.spacing()

   Return a 3-tuple ``(spc_description, spc_rows, spc_columns)`` describing
   the spacing within and between menu items.  `spc_description` is the
   number of spaces between an item name and its description. The menu system
   inserts the value of :meth:`pad` in the middle of this spacing area and
   fills the remaining parts with spaces. `spc_rows` is the number of rows
   used for each item. `spc_columns` is the number of blanks between columns
   of items.


.. method:: Menu.top_row()

   Return the number of the row that is currently at the top of the menu's
   display window.


.. method:: Menu.unpost()

   Erase the menu from its associated window.


.. method:: Menu.userptr()

   Return the user pointer for the menu.


.. method:: Menu.win()

   Return the menu's main window, which is used to display a title and/or 
   border.  This defaults to the ``stdscr``. 


Constants
---------

The :mod:`curses.menu` module defines the following data members:

.. data:: version

   A string representing the current version of the module. Also available as
   :const:`__version__`.

.. _curses-menu-item-options:

Constants are available to set options on items. All are on by default:

+-----------------------+-----------------------------------+
| Option                | Meaning                           |
+=======================+===================================+
| :const:`O_SELECTABLE` | Item is selectable from its menu. |
+-----------------------+-----------------------------------+

.. _curses-menu-menu-options:

Constants are available to set options on menus. All are on by default:

+-----------------------+--------------------------------------------------+
| Option                | Meaning                                          |
+=======================+==================================================+
| :const:`O_IGNORECASE` | Ignore the case when pattern-matching.           |
+-----------------------+--------------------------------------------------+
| :const:`O_NONCYCLIC`  | Don't wrap around to the other side of the menu. |
+-----------------------+--------------------------------------------------+
| :const:`O_ONEVALUE`   | Only one item can be selected at a time.         |
+-----------------------+--------------------------------------------------+
| :const:`O_ROWMAJOR`   | Display the menu in row-major order.             |
+-----------------------+--------------------------------------------------+
| :const:`O_SHOWDESC`   | Display the item descriptions when the menu is   |
|                       | posted.                                          |
+-----------------------+--------------------------------------------------+
| :const:`O_SHOWMATCH`  | Move the cursor to within the item name while    |
|                       | pattern-matching.                                |
+-----------------------+--------------------------------------------------+

.. _curses-menu-requests:

Menu driver requests are constants beginning with ``REQ_``:

+----------------------------+------------------------------------------------+
| Request                    | Meaning                                        |
+============================+================================================+
| :const:`REQ_DOWN_ITEM`     | Move down to an item.                          |
+----------------------------+------------------------------------------------+
| :const:`REQ_LEFT_ITEM`     | Move left to an item.                          |
+----------------------------+------------------------------------------------+
| :const:`REQ_RIGHT_ITEM`    | Move right to an item.                         |
+----------------------------+------------------------------------------------+
| :const:`REQ_UP_ITEM`       | Move up to an item.                            |
+----------------------------+------------------------------------------------+
| :const:`REQ_SCR_DLINE`     | Scroll down a line.                            |
+----------------------------+------------------------------------------------+
| :const:`REQ_SCR_DPAGE`     | Scroll down a page.                            |
+----------------------------+------------------------------------------------+
| :const:`REQ_SCR_ULINE`     | Scroll up a line.                              |
+----------------------------+------------------------------------------------+
| :const:`REQ_SCR_UPAGE`     | Scroll up a page.                              |
+----------------------------+------------------------------------------------+
| :const:`REQ_FIRST_ITEM`    | Move to the first item.                        |
+----------------------------+------------------------------------------------+
| :const:`REQ_LAST_ITEM`     | Move to the last item.                         |
+----------------------------+------------------------------------------------+
| :const:`REQ_NEXT_ITEM`     | Move to the next item.                         |
+----------------------------+------------------------------------------------+
| :const:`REQ_PREV_ITEM`     | Move to the previous item.                     |
+----------------------------+------------------------------------------------+
| :const:`REQ_TOGGLE_ITEM`   | Select/deselect an item.                       |
+----------------------------+------------------------------------------------+
| :const:`REQ_CLEAR_PATTERN` | Clear the menu pattern buffer.                 |
+----------------------------+------------------------------------------------+
| :const:`REQ_BACK_PATTERN`  | Delete the previous character from the pattern |
|                            | buffer.                                        |
+----------------------------+------------------------------------------------+
| :const:`REQ_NEXT_MATCH`    | Move to the next item matching the pattern     |
|                            | buffer.                                        |
+----------------------------+------------------------------------------------+
| :const:`REQ_PREV_MATCH`    | Move to the previous item matching the pattern |
|                            | buffer.                                        |
+----------------------------+------------------------------------------------+

You can define application-specific commands relative to the menu command
constants:

+---------------------------+------------------------------------------------+
| Constant                  | Meaning                                        |
+===========================+================================================+
| :const:`MIN_MENU_COMMAND` | The minimum allowable value for pre-defined    |
|                           | requests.                                      |
+---------------------------+------------------------------------------------+
| :const:`MAX_MENU_COMMAND` | The maximum allowable value for pre-defined    |
|                           | requests.                                      |
+---------------------------+------------------------------------------------+
