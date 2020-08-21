#
# Test script for the curses module
#
# This script doesn't actually display anything very coherent. but it
# does call (nearly) every method and function.
#
# Functions not tested: {def,reset}_{shell,prog}_mode, getch(), getstr(),
# init_color()
# Only called, not tested: getmouse(), ungetmouse()
#

import os
import string
import sys
import tempfile
import unittest

from test.support import requires, verbose, SaveSignals
from test.support.import_helper import import_module

# Optionally test curses module.  This currently requires that the
# 'curses' resource be given on the regrtest command line using the -u
# option.  If not available, nothing after this line will be executed.
import inspect
requires('curses')

# If either of these don't exist, skip the tests.
curses = import_module('curses')
import_module('curses.ascii')
import_module('curses.textpad')
try:
    import curses.panel
except ImportError:
    pass
try:
    import curses.menu
except ImportError:
    pass

def requires_curses_func(name):
    return unittest.skipUnless(hasattr(curses, name),
                               'requires curses.%s' % name)

term = os.environ.get('TERM')

# If newterm was supported we could use it instead of initscr and not exit
@unittest.skipIf(not term or term == 'unknown',
                 "$TERM=%r, calling initscr() may cause exit" % term)
@unittest.skipIf(sys.platform == 'cygwin',
                 "cygwin's curses mostly just hangs")
class TestCurses(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        if not sys.__stdout__.isatty():
            # Temporary skip tests on non-tty
            raise unittest.SkipTest('sys.__stdout__ is not a tty')
            cls.tmp = tempfile.TemporaryFile()
            fd = cls.tmp.fileno()
        else:
            cls.tmp = None
            fd = sys.__stdout__.fileno()
        # testing setupterm() inside initscr/endwin
        # causes terminal breakage
        curses.setupterm(fd=fd)

    @classmethod
    def tearDownClass(cls):
        if cls.tmp:
            cls.tmp.close()
            del cls.tmp

    def setUp(self):
        self.save_signals = SaveSignals()
        self.save_signals.save()
        if verbose:
            # just to make the test output a little more readable
            print()
        self.stdscr = curses.initscr()
        curses.savetty()

    def tearDown(self):
        curses.resetty()
        curses.endwin()
        self.save_signals.restore()

    def test_window_funcs(self):
        'Test the methods of windows'
        stdscr = self.stdscr
        win = curses.newwin(10,10)
        win = curses.newwin(5,5, 5,5)
        win2 = curses.newwin(15,15, 5,5)

        for meth in [stdscr.addch, stdscr.addstr]:
            for args in [('a',), ('a', curses.A_BOLD),
                         (4,4, 'a'), (5,5, 'a', curses.A_BOLD)]:
                with self.subTest(meth=meth.__qualname__, args=args):
                    meth(*args)

        for meth in [stdscr.clear, stdscr.clrtobot,
                     stdscr.clrtoeol, stdscr.cursyncup, stdscr.delch,
                     stdscr.deleteln, stdscr.erase, stdscr.getbegyx,
                     stdscr.getbkgd, stdscr.getkey, stdscr.getmaxyx,
                     stdscr.getparyx, stdscr.getyx, stdscr.inch,
                     stdscr.insertln, stdscr.instr, stdscr.is_wintouched,
                     win.noutrefresh, stdscr.redrawwin, stdscr.refresh,
                     stdscr.standout, stdscr.standend, stdscr.syncdown,
                     stdscr.syncup, stdscr.touchwin, stdscr.untouchwin]:
            with self.subTest(meth=meth.__qualname__):
                meth()

        stdscr.addnstr('1234', 3)
        stdscr.addnstr('1234', 3, curses.A_BOLD)
        stdscr.addnstr(4,4, '1234', 3)
        stdscr.addnstr(5,5, '1234', 3, curses.A_BOLD)

        stdscr.attron(curses.A_BOLD)
        stdscr.attroff(curses.A_BOLD)
        stdscr.attrset(curses.A_BOLD)
        stdscr.bkgd(' ')
        stdscr.bkgd(' ', curses.A_REVERSE)
        stdscr.bkgdset(' ')
        stdscr.bkgdset(' ', curses.A_REVERSE)

        win.border(65, 66, 67, 68,
                   69, 70, 71, 72)
        win.border('|', '!', '-', '_',
                   '+', '\\', '#', '/')
        with self.assertRaises(TypeError,
                               msg='Expected win.border() to raise TypeError'):
            win.border(65, 66, 67, 68,
                       69, [], 71, 72)

        win.box(65, 67)
        win.box('!', '_')
        win.box(b':', b'~')
        self.assertRaises(TypeError, win.box, 65, 66, 67)
        self.assertRaises(TypeError, win.box, 65)
        win.box()

        stdscr.clearok(1)

        win4 = stdscr.derwin(2,2)
        win4 = stdscr.derwin(1,1, 5,5)
        win4.mvderwin(9,9)

        stdscr.echochar('a')
        stdscr.echochar('a', curses.A_BOLD)
        stdscr.hline('-', 5)
        stdscr.hline('-', 5, curses.A_BOLD)
        stdscr.hline(1,1,'-', 5)
        stdscr.hline(1,1,'-', 5, curses.A_BOLD)

        stdscr.idcok(1)
        stdscr.idlok(1)
        if hasattr(stdscr, 'immedok'):
            stdscr.immedok(1)
            stdscr.immedok(0)
        stdscr.insch('c')
        stdscr.insdelln(1)
        stdscr.insnstr('abc', 3)
        stdscr.insnstr('abc', 3, curses.A_BOLD)
        stdscr.insnstr(5, 5, 'abc', 3)
        stdscr.insnstr(5, 5, 'abc', 3, curses.A_BOLD)

        stdscr.insstr('def')
        stdscr.insstr('def', curses.A_BOLD)
        stdscr.insstr(5, 5, 'def')
        stdscr.insstr(5, 5, 'def', curses.A_BOLD)
        stdscr.is_linetouched(0)
        stdscr.keypad(1)
        stdscr.leaveok(1)
        stdscr.move(3,3)
        win.mvwin(2,2)
        stdscr.nodelay(1)
        stdscr.notimeout(1)
        win2.overlay(win)
        win2.overwrite(win)
        win2.overlay(win, 1, 2, 2, 1, 3, 3)
        win2.overwrite(win, 1, 2, 2, 1, 3, 3)
        stdscr.redrawln(1,2)

        stdscr.scrollok(1)
        stdscr.scroll()
        stdscr.scroll(2)
        stdscr.scroll(-3)

        stdscr.move(12, 2)
        stdscr.setscrreg(10,15)
        win3 = stdscr.subwin(10,10)
        win3 = stdscr.subwin(10,10, 5,5)
        if hasattr(stdscr, 'syncok') and not sys.platform.startswith('sunos'):
            stdscr.syncok(1)
        stdscr.timeout(5)
        stdscr.touchline(5,5)
        stdscr.touchline(5,5,0)
        stdscr.vline('a', 3)
        stdscr.vline('a', 3, curses.A_STANDOUT)
        if hasattr(stdscr, 'chgat'):
            stdscr.chgat(5, 2, 3, curses.A_BLINK)
            stdscr.chgat(3, curses.A_BOLD)
            stdscr.chgat(5, 8, curses.A_UNDERLINE)
            stdscr.chgat(curses.A_BLINK)
        stdscr.refresh()

        stdscr.vline(1,1, 'a', 3)
        stdscr.vline(1,1, 'a', 3, curses.A_STANDOUT)

        if hasattr(stdscr, 'resize'):
            stdscr.resize(25, 80)
        if hasattr(stdscr, 'enclose'):
            stdscr.enclose(10, 10)

        self.assertRaises(ValueError, stdscr.getstr, -400)
        self.assertRaises(ValueError, stdscr.getstr, 2, 3, -400)
        self.assertRaises(ValueError, stdscr.instr, -2)
        self.assertRaises(ValueError, stdscr.instr, 2, 3, -2)

    def test_embedded_null_chars(self):
        # reject embedded null bytes and characters
        stdscr = self.stdscr
        for arg in ['a', b'a']:
            with self.subTest(arg=arg):
                self.assertRaises(ValueError, stdscr.addstr, 'a\0')
                self.assertRaises(ValueError, stdscr.addnstr, 'a\0', 1)
                self.assertRaises(ValueError, stdscr.insstr, 'a\0')
                self.assertRaises(ValueError, stdscr.insnstr, 'a\0', 1)

    def test_module_funcs(self):
        'Test module-level functions'
        for func in [curses.baudrate, curses.beep, curses.can_change_color,
                     curses.cbreak, curses.def_prog_mode, curses.doupdate,
                     curses.flash, curses.flushinp,
                     curses.has_colors, curses.has_ic, curses.has_il,
                     curses.isendwin, curses.killchar, curses.longname,
                     curses.nocbreak, curses.noecho, curses.nonl,
                     curses.noqiflush, curses.noraw,
                     curses.reset_prog_mode, curses.termattrs,
                     curses.termname, curses.erasechar,
                     curses.has_extended_color_support]:
            with self.subTest(func=func.__qualname__):
                func()
        if hasattr(curses, 'filter'):
            curses.filter()
        if hasattr(curses, 'getsyx'):
            curses.getsyx()

        # Functions that actually need arguments
        if curses.tigetstr('cnorm'):
            curses.curs_set(1)
        curses.delay_output(1)
        curses.echo() ; curses.echo(1)

        with tempfile.TemporaryFile() as f:
            self.stdscr.putwin(f)
            f.seek(0)
            curses.getwin(f)

        curses.halfdelay(1)
        curses.intrflush(1)
        curses.meta(1)
        curses.napms(100)
        curses.newpad(50,50)
        win = curses.newwin(5,5)
        win = curses.newwin(5,5, 1,1)
        curses.nl() ; curses.nl(1)
        curses.putp(b'abc')
        curses.qiflush()
        curses.raw() ; curses.raw(1)
        curses.set_escdelay(25)
        self.assertEqual(curses.get_escdelay(), 25)
        curses.set_tabsize(4)
        self.assertEqual(curses.get_tabsize(), 4)
        if hasattr(curses, 'setsyx'):
            curses.setsyx(5,5)
        curses.tigetflag('hc')
        curses.tigetnum('co')
        curses.tigetstr('cr')
        curses.tparm(b'cr')
        if hasattr(curses, 'typeahead'):
            curses.typeahead(sys.__stdin__.fileno())
        curses.unctrl('a')
        curses.ungetch('a')
        if hasattr(curses, 'use_env'):
            curses.use_env(1)

    # Functions only available on a few platforms
    def test_colors_funcs(self):
        if not curses.has_colors():
            self.skipTest('requires colors support')
        curses.start_color()
        curses.init_pair(2, 1,1)
        curses.color_content(1)
        curses.color_pair(2)
        curses.pair_content(curses.COLOR_PAIRS - 1)
        curses.pair_number(0)

        if hasattr(curses, 'use_default_colors'):
            curses.use_default_colors()

        self.assertRaises(ValueError, curses.color_content, -1)
        self.assertRaises(ValueError, curses.color_content, curses.COLORS + 1)
        self.assertRaises(ValueError, curses.color_content, -2**31 - 1)
        self.assertRaises(ValueError, curses.color_content, 2**31)
        self.assertRaises(ValueError, curses.color_content, -2**63 - 1)
        self.assertRaises(ValueError, curses.color_content, 2**63 - 1)
        self.assertRaises(ValueError, curses.pair_content, -1)
        self.assertRaises(ValueError, curses.pair_content, curses.COLOR_PAIRS)
        self.assertRaises(ValueError, curses.pair_content, -2**31 - 1)
        self.assertRaises(ValueError, curses.pair_content, 2**31)
        self.assertRaises(ValueError, curses.pair_content, -2**63 - 1)
        self.assertRaises(ValueError, curses.pair_content, 2**63 - 1)

    @requires_curses_func('keyname')
    def test_keyname(self):
        curses.keyname(13)

    @requires_curses_func('has_key')
    def test_has_key(self):
        curses.has_key(13)

    @requires_curses_func('getmouse')
    def test_getmouse(self):
        (availmask, oldmask) = curses.mousemask(curses.BUTTON1_PRESSED)
        if availmask == 0:
            self.skipTest('mouse stuff not available')
        curses.mouseinterval(10)
        # just verify these don't cause errors
        curses.ungetmouse(0, 0, 0, 0, curses.BUTTON1_PRESSED)
        m = curses.getmouse()

    @requires_curses_func('panel')
    def test_userptr_without_set(self):
        w = curses.newwin(10, 10)
        p = curses.panel.new_panel(w)
        # try to access userptr() before calling set_userptr() -- segfaults
        with self.assertRaises(curses.panel.error,
                               msg='userptr should fail since not set'):
            p.userptr()

    @requires_curses_func('panel')
    def test_userptr_memory_leak(self):
        w = curses.newwin(10, 10)
        p = curses.panel.new_panel(w)
        obj = object()
        nrefs = sys.getrefcount(obj)
        for i in range(100):
            p.set_userptr(obj)

        p.set_userptr(None)
        self.assertEqual(sys.getrefcount(obj), nrefs,
                         'set_userptr leaked references')

    @requires_curses_func('panel')
    def test_userptr_segfault(self):
        w = curses.newwin(10, 10)
        panel = curses.panel.new_panel(w)
        class A:
            def __del__(self):
                panel.set_userptr(None)
        panel.set_userptr(A())
        panel.set_userptr(None)

    @requires_curses_func('panel')
    def test_new_curses_panel(self):
        w = curses.newwin(10, 10)
        panel = curses.panel.new_panel(w)
        self.assertRaises(TypeError, type(panel))

    @requires_curses_func('menu')
    def test_curses_menu_item_new(self):
        item1 = curses.menu.new_item('my name')
        self.assertEqual(b'my name', item1.name())
        self.assertIsNone(item1.description())

        item2 = curses.menu.new_item('my name', 'my description')
        self.assertEqual(b'my name', item2.name())
        self.assertEqual(b'my description', item2.description())

        item2 = curses.menu.new_item(b'\x80\x81\x82', b'\x85\x81\x83')
        self.assertEqual(b'\x80\x81\x82', item2.name())
        self.assertEqual(b'\x85\x81\x83', item2.description())

    @requires_curses_func('menu')
    def test_curses_menu_item_userptr(self):
        item = curses.menu.new_item('item')

        self.assertRaises(curses.menu.error, item.userptr)
        obj = object()
        item.set_userptr(obj)
        self.assertEqual(obj, item.userptr())
        obj_id = id(obj)
        del obj
        obj = item.userptr()
        self.assertIsNotNone(obj)
        self.assertEqual(obj_id, id(obj))

    @requires_curses_func('menu')
    def test_curses_menu_item_value(self):
        item = curses.menu.new_item('item')

        self.assertFalse(item.value())
        item.set_value(True)
        self.assertTrue(item.value())
        item.set_value(False)
        self.assertFalse(item.value())

    @requires_curses_func('menu')
    def test_curses_menu_item_visible(self):
        item = curses.menu.new_item('item')

        # FIXME: should be tested in posted menu
        self.assertFalse(item.visible())

    @requires_curses_func('menu')
    def test_curses_menu_item_opts(self):
        self.assertTrue(hasattr(curses.menu, 'O_SELECTABLE'))

        item = curses.menu.new_item('item')

        item.set_opts(0)
        self.assertEqual(0, item.opts())
        item.opts_on(curses.menu.O_SELECTABLE)
        self.assertEqual(curses.menu.O_SELECTABLE, item.opts())
        item.opts_off(curses.menu.O_SELECTABLE)
        self.assertEqual(0, item.opts())

    @requires_curses_func('menu')
    def test_curses_menu_menu_opts(self):
        self.assertTrue(hasattr(curses.menu, 'O_ONEVALUE'))
        self.assertTrue(hasattr(curses.menu, 'O_SHOWDESC'))
        self.assertTrue(hasattr(curses.menu, 'O_ROWMAJOR'))
        self.assertTrue(hasattr(curses.menu, 'O_IGNORECASE'))
        self.assertTrue(hasattr(curses.menu, 'O_SHOWMATCH'))
        self.assertTrue(hasattr(curses.menu, 'O_NONCYCLIC'))
        self.assertTrue(hasattr(curses.menu, 'O_MOUSE_MENU'))

    def _create_simple_menu(self, nb=3):
        import itertools
        names = ('Apple', 'Pear', 'Orange')
        items = tuple(curses.menu.new_item(name) for _, name in zip(range(nb), itertools.cycle(names)))
        return items, curses.menu.new_menu(items)

    @requires_curses_func('menu')
    def test_curses_menu_menu_items(self):
        items, menu = self._create_simple_menu()
        self.assertTupleEqual(items, menu.items())
        self.assertEqual(len(items), menu.count())

        names2 = ('Salad', 'Tomato', 'Carrot', "Cucumber")
        items2 = tuple(curses.menu.new_item(name2) for name2 in names2)

        with self.assertRaises(ValueError):
            menu.set_items(items2 + (None,))
        self.assertTupleEqual(items, menu.items())

        self.assertNotEqual(len(items), len(items2))

        menu.set_items(items2)
        self.assertTupleEqual(items2, menu.items())
        self.assertEqual(len(items2), menu.count())

    @requires_curses_func('menu')
    def test_curses_menu_menu_item_current(self):
        short_items, short_menu = self._create_simple_menu(2)
        with self.assertRaises(curses.menu.error):
            short_menu.set_top_row(1)

        items, menu = self._create_simple_menu(50)

        self.assertEqual(items[0], menu.current_item())
        menu.set_current_item(items[1])
        self.assertEqual(items[1], menu.current_item())

        self.assertEqual(0, menu.top_row())
        menu.set_top_row(1)
        self.assertEqual(1, menu.top_row())

        self.assertEqual(1, items[1].index())

        new_item = curses.menu.new_item("new_item")
        with self.assertRaises(curses.menu.error):
            new_item.index()

        menu.set_current_item(items[1])
        with self.assertRaises(curses.menu.error):
            menu.set_current_item(None)
        self.assertIsNotNone(menu.current_item())

    @requires_curses_func('menu')
    def test_curses_menu_menu_format(self):
        _, menu = self._create_simple_menu()

        self.assertTupleEqual((16, 1), menu.format())
        menu.set_format(5, 5)
        self.assertTupleEqual((5, 5), menu.format())

    @requires_curses_func('menu')
    def test_curses_menu_menu_attributes(self):
        _, menu = self._create_simple_menu()

        self.assertEqual(curses.A_REVERSE, menu.fore())
        menu.set_fore(curses.A_BOLD)
        self.assertEqual(curses.A_BOLD, menu.fore())

        self.assertEqual(curses.A_NORMAL, menu.back())
        menu.set_back(curses.A_NORMAL)
        self.assertEqual(curses.A_NORMAL, menu.back())

        self.assertEqual(curses.A_UNDERLINE, menu.grey())
        menu.set_grey(curses.A_DIM)
        self.assertEqual(curses.A_DIM, menu.grey())

        self.assertEqual(curses.ascii.SP, menu.pad())
        menu.set_pad(ord('*'))
        self.assertEqual(ord('*'), menu.pad())
        menu.set_pad(ord('/'))
        self.assertEqual(ord('/'), menu.pad())

    @requires_curses_func('menu')
    def test_curses_menu_menu_mark(self):
        _, menu = self._create_simple_menu()

        self.assertEqual(b'-', menu.mark())
        menu.set_mark('*')
        self.assertEqual(b'*', menu.mark())

    @requires_curses_func('menu')
    def test_curses_menu_menu_spacing(self):
        _, menu = self._create_simple_menu()

        menu_spacing = menu.spacing()
        self.assertIsInstance(menu_spacing, tuple)
        self.assertTrue(3, len(menu_spacing))
        menu.set_spacing(1, 2, 3)
        self.assertTupleEqual((1, 2, 3), menu.spacing())

    @requires_curses_func('menu')
    def test_curses_menu_menu_userptr(self):
        _, menu = self._create_simple_menu()

        with self.assertRaises(curses.menu.error):
            menu.userptr()
        obj = object()
        menu.set_userptr(obj)
        self.assertEqual(obj, menu.userptr())
        obj_id = id(obj)
        del obj
        obj = menu.userptr()
        self.assertEqual(obj_id, id(obj))

    @requires_curses_func('menu')
    def test_curses_menu_menu_pattern_buffer(self):
        _, menu = self._create_simple_menu()

        self.assertIsInstance(menu.pattern(), bytes)
        menu.set_pattern("Sal")
        self.assertEqual(b"Sal", menu.pattern())

    @requires_curses_func('menu')
    def test_curses_menu_menu_windows(self):
        _, menu = self._create_simple_menu()

        w1 = curses.newwin(10, 10)
        w2 = curses.newwin(8, 8, 1, 1)

        self.assertEqual(self.stdscr, menu.win())
        self.assertEqual(self.stdscr, menu.sub())
        menu.set_win(w1)
        menu.set_sub(w2)
        self.assertEqual(w1, menu.win())
        self.assertEqual(w2, menu.sub())

        del menu
        del w1
        del w2

    @requires_curses_func('menu')
    def test_curses_menu_menu_post(self):
        _, menu = self._create_simple_menu()

        menu.post()
        self.assertRaises(curses.error, menu.post)
        menu.unpost()

    @requires_curses_func('menu')
    def test_curses_menu_menu_hook(self):
        _, menu = self._create_simple_menu()

        with self.assertRaises(curses.menu.error):
            menu.item_init()
        with self.assertRaises(curses.menu.error):
            menu.item_term()
        with self.assertRaises(curses.menu.error):
            menu.menu_init()
        with self.assertRaises(curses.menu.error):
            menu.menu_term()

        with self.assertRaises(curses.menu.error):
            menu.set_item_init(object())

        called = {
            'item_init': None,
            'item_term': None,
            'menu_init': None,
            'menu_term': None,
        }

        class ObjHook(object):
            def __init__(self, key):
                self.key = key

            def __call__(self, menu):
                called[self.key] = menu

        o_item_init = ObjHook('item_init')
        o_item_term = ObjHook('item_term')
        o_menu_init = ObjHook('menu_init')
        o_menu_term = ObjHook('menu_term')
        menu.set_item_init(o_item_init)
        menu.set_item_term(o_item_term)
        menu.set_menu_init(o_menu_init)
        menu.set_menu_term(o_menu_term)
        self.assertEqual(o_item_init, menu.item_init())
        self.assertEqual(o_item_term, menu.item_term())
        self.assertEqual(o_menu_init, menu.menu_init())
        self.assertEqual(o_menu_term, menu.menu_term())
        del o_item_init
        del o_item_term
        del o_menu_init
        del o_menu_term

        self.assertTrue(all(w is None for w in called.values()))

        menu.post()
        # self.assertEqual(menu, called['item_init'])
        # self.assertIsNone(called['item_term'])
        # self.assertEqual(menu, called['menu_init'])
        # self.assertIsNone(called['menu_term'])
        # menu['item_init'] = None
        # menu['menu_init'] = None
        #
        # menu.unpost()
        # self.assertIsNone(called['item_init'])
        # self.assertEqual(menu, called['item_term'])
        # self.assertIsNone(called['menu_init'])
        # self.assertEqual(menu, called['menu_term'])

    @requires_curses_func('menu')
    def test_new_curses_menu(self):
        items, menu = self._create_simple_menu()

        self.assertEqual(items, menu.items())
        menu.set_back(curses.A_REVERSE)
        self.assertEqual(curses.A_REVERSE, menu.back())
        menu.set_current_item(items[1])
        self.assertEqual(items[1], menu.current_item())
        menu.set_fore(curses.A_BLINK)
        self.assertEqual(curses.A_BLINK, menu.fore())
        menu.set_format(4, 2)
        self.assertEqual((4, 2), menu.format())
        menu.set_grey(curses.A_UNDERLINE)
        self.assertEqual(curses.A_UNDERLINE, menu.grey())
        menu.set_mark('&')
        self.assertEqual(b'&', menu.mark())
        menu.set_opts(curses.menu.O_SHOWMATCH)
        self.assertEqual(curses.menu.O_SHOWMATCH, menu.opts())
        menu.set_pad(ord('#'))
        self.assertEqual(ord('#'), menu.pad())
        menu.set_pattern('<>')
        self.assertEqual(b'<>', menu.pattern())
        menu.set_top_row(1)
        self.assertEqual(1, menu.top_row())
        menu.set_spacing(3, 2, 2)
        self.assertEqual((3, 2, 2), menu.spacing())
        menu.set_items(items2)
        self.assertEqual(items2, menu.items())

        menu.opts_on(menu.O_SHOWDESC)
        self.assertNotEqual(0, menu.opts() & curses.menu.O_SHOWDESC)
        menu.opts_off(menu.O_SHOWDESC)
        self.assertEqual(0, menu.opts() & curses.menu.O_SHOWDESC)

        self.assertEqual(None, menu.userptr())
        menu.set_userptr(nil)
        self.assertEqual(nil, menu.userptr())

    @requires_curses_func('menu')
    def test_curses_menu_menu_driver(self):
        self.assertTrue(hasattr(curses.menu, 'REQ_LEFT_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_RIGHT_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_UP_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_DOWN_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_SCR_ULINE'))
        self.assertTrue(hasattr(curses.menu, 'REQ_SCR_DLINE'))
        self.assertTrue(hasattr(curses.menu, 'REQ_SCR_DPAGE'))
        self.assertTrue(hasattr(curses.menu, 'REQ_SCR_UPAGE'))
        self.assertTrue(hasattr(curses.menu, 'REQ_FIRST_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_LAST_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_NEXT_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_PREV_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_TOGGLE_ITEM'))
        self.assertTrue(hasattr(curses.menu, 'REQ_CLEAR_PATTERN'))
        self.assertTrue(hasattr(curses.menu, 'REQ_BACK_PATTERN'))
        self.assertTrue(hasattr(curses.menu, 'REQ_NEXT_MATCH'))
        self.assertTrue(hasattr(curses.menu, 'REQ_PREV_MATCH'))

    @requires_curses_func('menu')
    def test_curses_menu_requestname(self):
        self.assertEqual('LEFT_ITEM', curses.menu.request_name(curses.menu.REQ_LEFT_ITEM))
        self.assertEqual(curses.menu.REQ_CLEAR_PATTERN, curses.menu.request_by_name('CLEAR_PATTERN'))
        with self.assertRaises(curses.menu.error):
            curses.menu.request_name(0x0)
        with self.assertRaises(curses.menu.error):
            curses.menu.request_by_name('NON_EXISTENT_REQUEST')

    @requires_curses_func('is_term_resized')
    def test_is_term_resized(self):
        curses.is_term_resized(*self.stdscr.getmaxyx())

    @requires_curses_func('resize_term')
    def test_resize_term(self):
        curses.resize_term(*self.stdscr.getmaxyx())

    @requires_curses_func('resizeterm')
    def test_resizeterm(self):
        lines, cols = curses.LINES, curses.COLS
        new_lines = lines - 1
        new_cols = cols + 1
        curses.resizeterm(new_lines, new_cols)

        self.assertEqual(curses.LINES, new_lines)
        self.assertEqual(curses.COLS, new_cols)

    def test_issue6243(self):
        curses.ungetch(1025)
        self.stdscr.getkey()

    @requires_curses_func('unget_wch')
    @unittest.skipIf(getattr(curses, 'ncurses_version', (99,)) < (5, 8),
                     'unget_wch is broken in ncurses 5.7 and earlier')
    def test_unget_wch(self):
        stdscr = self.stdscr
        encoding = stdscr.encoding
        for ch in ('a', '\xe9', '\u20ac', '\U0010FFFF'):
            try:
                ch.encode(encoding)
            except UnicodeEncodeError:
                continue
            try:
                curses.unget_wch(ch)
            except Exception as err:
                self.fail('unget_wch(%a) failed with encoding %s: %s'
                          % (ch, stdscr.encoding, err))
            read = stdscr.get_wch()
            self.assertEqual(read, ch)

            code = ord(ch)
            curses.unget_wch(code)
            read = stdscr.get_wch()
            self.assertEqual(read, ch)

    def test_issue10570(self):
        b = curses.tparm(curses.tigetstr('cup'), 5, 3)
        self.assertIs(type(b), bytes)

    def test_encoding(self):
        stdscr = self.stdscr
        import codecs
        encoding = stdscr.encoding
        codecs.lookup(encoding)
        with self.assertRaises(TypeError):
            stdscr.encoding = 10
        stdscr.encoding = encoding
        with self.assertRaises(TypeError):
            del stdscr.encoding

    def test_issue21088(self):
        stdscr = self.stdscr
        #
        # http://bugs.python.org/issue21088
        #
        # the bug:
        # when converting curses.window.addch to Argument Clinic
        # the first two parameters were switched.

        # if someday we can represent the signature of addch
        # we will need to rewrite this test.
        try:
            signature = inspect.signature(stdscr.addch)
            self.assertFalse(signature)
        except ValueError:
            # not generating a signature is fine.
            pass

        # So.  No signature for addch.
        # But Argument Clinic gave us a human-readable equivalent
        # as the first line of the docstring.  So we parse that,
        # and ensure that the parameters appear in the correct order.
        # Since this is parsing output from Argument Clinic, we can
        # be reasonably certain the generated parsing code will be
        # correct too.
        human_readable_signature = stdscr.addch.__doc__.split('\n')[0]
        self.assertIn('[y, x,]', human_readable_signature)

    def test_issue13051(self):
        stdscr = self.stdscr
        if not hasattr(stdscr, 'resize'):
            raise unittest.SkipTest('requires curses.window.resize')
        box = curses.textpad.Textbox(stdscr, insert_mode=True)
        lines, cols = stdscr.getmaxyx()
        stdscr.resize(lines-2, cols-2)
        # this may cause infinite recursion, leading to a RuntimeError
        box._insert_printable_char('a')


class MiscTests(unittest.TestCase):

    @requires_curses_func('update_lines_cols')
    def test_update_lines_cols(self):
        # this doesn't actually test that LINES and COLS are updated,
        # because we can't automate changing them. See Issue #4254 for
        # a manual test script. We can only test that the function
        # can be called.
        curses.update_lines_cols()

    @requires_curses_func('ncurses_version')
    def test_ncurses_version(self):
        v = curses.ncurses_version
        self.assertIsInstance(v[:], tuple)
        self.assertEqual(len(v), 3)
        self.assertIsInstance(v[0], int)
        self.assertIsInstance(v[1], int)
        self.assertIsInstance(v[2], int)
        self.assertIsInstance(v.major, int)
        self.assertIsInstance(v.minor, int)
        self.assertIsInstance(v.patch, int)
        self.assertEqual(v[0], v.major)
        self.assertEqual(v[1], v.minor)
        self.assertEqual(v[2], v.patch)
        self.assertGreaterEqual(v.major, 0)
        self.assertGreaterEqual(v.minor, 0)
        self.assertGreaterEqual(v.patch, 0)

class TestAscii(unittest.TestCase):

    def test_controlnames(self):
        for name in curses.ascii.controlnames:
            self.assertTrue(hasattr(curses.ascii, name), name)

    def test_ctypes(self):
        def check(func, expected):
            with self.subTest(ch=c, func=func):
                self.assertEqual(func(i), expected)
                self.assertEqual(func(c), expected)

        for i in range(256):
            c = chr(i)
            b = bytes([i])
            check(curses.ascii.isalnum, b.isalnum())
            check(curses.ascii.isalpha, b.isalpha())
            check(curses.ascii.isdigit, b.isdigit())
            check(curses.ascii.islower, b.islower())
            check(curses.ascii.isspace, b.isspace())
            check(curses.ascii.isupper, b.isupper())

            check(curses.ascii.isascii, i < 128)
            check(curses.ascii.ismeta, i >= 128)
            check(curses.ascii.isctrl, i < 32)
            check(curses.ascii.iscntrl, i < 32 or i == 127)
            check(curses.ascii.isblank, c in ' \t')
            check(curses.ascii.isgraph, 32 < i <= 126)
            check(curses.ascii.isprint, 32 <= i <= 126)
            check(curses.ascii.ispunct, c in string.punctuation)
            check(curses.ascii.isxdigit, c in string.hexdigits)

        for i in (-2, -1, 256, sys.maxunicode, sys.maxunicode+1):
            self.assertFalse(curses.ascii.isalnum(i))
            self.assertFalse(curses.ascii.isalpha(i))
            self.assertFalse(curses.ascii.isdigit(i))
            self.assertFalse(curses.ascii.islower(i))
            self.assertFalse(curses.ascii.isspace(i))
            self.assertFalse(curses.ascii.isupper(i))

            self.assertFalse(curses.ascii.isascii(i))
            self.assertFalse(curses.ascii.isctrl(i))
            self.assertFalse(curses.ascii.iscntrl(i))
            self.assertFalse(curses.ascii.isblank(i))
            self.assertFalse(curses.ascii.isgraph(i))
            self.assertFalse(curses.ascii.isprint(i))
            self.assertFalse(curses.ascii.ispunct(i))
            self.assertFalse(curses.ascii.isxdigit(i))

        self.assertFalse(curses.ascii.ismeta(-1))

    def test_ascii(self):
        ascii = curses.ascii.ascii
        self.assertEqual(ascii('\xc1'), 'A')
        self.assertEqual(ascii('A'), 'A')
        self.assertEqual(ascii(ord('\xc1')), ord('A'))

    def test_ctrl(self):
        ctrl = curses.ascii.ctrl
        self.assertEqual(ctrl('J'), '\n')
        self.assertEqual(ctrl('\n'), '\n')
        self.assertEqual(ctrl('@'), '\0')
        self.assertEqual(ctrl(ord('J')), ord('\n'))

    def test_alt(self):
        alt = curses.ascii.alt
        self.assertEqual(alt('\n'), '\x8a')
        self.assertEqual(alt('A'), '\xc1')
        self.assertEqual(alt(ord('A')), 0xc1)

    def test_unctrl(self):
        unctrl = curses.ascii.unctrl
        self.assertEqual(unctrl('a'), 'a')
        self.assertEqual(unctrl('A'), 'A')
        self.assertEqual(unctrl(';'), ';')
        self.assertEqual(unctrl(' '), ' ')
        self.assertEqual(unctrl('\x7f'), '^?')
        self.assertEqual(unctrl('\n'), '^J')
        self.assertEqual(unctrl('\0'), '^@')
        self.assertEqual(unctrl(ord('A')), 'A')
        self.assertEqual(unctrl(ord('\n')), '^J')
        # Meta-bit characters
        self.assertEqual(unctrl('\x8a'), '!^J')
        self.assertEqual(unctrl('\xc1'), '!A')
        self.assertEqual(unctrl(ord('\x8a')), '!^J')
        self.assertEqual(unctrl(ord('\xc1')), '!A')


if __name__ == '__main__':
    unittest.main()
