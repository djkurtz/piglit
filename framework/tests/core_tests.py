# Copyright (c) 2014 Intel Corporation

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

""" Module providing tests for the core module """


import os
import collections
import shutil
import ConfigParser
import textwrap
import nose.tools as nt
import framework.tests.utils as utils
import framework.core as core


def _reset_piglit_config():
    """ Set core.PIGLIT_CONFIG back to pristine """
    core.PIGLIT_CONFIG = ConfigParser.SafeConfigParser()


def check_initialize(target):
    """ Check that a class initializes without error """
    func = target()
    # Asserting that func exists will fail for Group and TestrunResult which
    # are dict subclasses
    assert isinstance(func, target)


@utils.nose_generator
def test_generate_initialize():
    """ Generator that creates tests to initialize all of the classes in core

    In a compiled language the compiler provides this kind of checking, but in
    an interpreted language like python you don't have a compiler test. The
    unit tests generated by this function serve as a similar test, does this
    even work?

    """
    yieldable = check_initialize

    for target in [core.Options]:
        yieldable.description = "Test that {} initializes".format(
            target.__name__)
        yield yieldable, target


def test_parse_listfile_return():
    """ Test that parse_listfile returns a container

    Given a file with a newline seperated list of results, parse_listfile
    should return a list of files with no whitespace

    """
    contents = "/tmp/foo\n/tmp/bar\n"

    with utils.with_tempfile(contents) as tfile:
        results = core.parse_listfile(tfile)

    assert isinstance(results, collections.Container)


def check_whitespace(actual, base, message):
    """ check that the string has not trailing whitespace """
    assert base == actual, message


def test_parse_listfile_whitespace():
    """ Test that parse_listfile remove whitespace """
    contents = "/tmp/foo\n/tmp/foo  \n/tmp/foo\t\n"

    with utils.with_tempfile(contents) as tfile:
        results = core.parse_listfile(tfile)

    yld = check_whitespace

    # Test for newlines
    yld.description = ("Test that trailing newlines are removed by "
                       "parse_listfile")
    yield yld, results[0], "/tmp/foo", "Trailing newline not removed!"

    # test for normal spaces
    yld.description = "Test that trailing spaces are removed by parse_listfile"
    yield yld, results[1], "/tmp/foo", "Trailing spaces not removed!"

    # test for tabs
    yld.description = "Test that trailing tabs are removed by parse_listfile"
    yield yld, results[2], "/tmp/foo", "Trailing tab not removed!"


def test_parse_listfile_tilde():
    """ Test that parse_listfile properly expands tildes

    According to the python docs for python 2.7
    (http://docs.python.org/2/library/os.path.html#module-os.path), both
    os.path.expanduser and os.path.expandvars work on both *nix systems (Linux,
    *BSD, OSX) and Windows.

    """
    contents = "~/foo\n"

    with utils.with_tempfile(contents) as tfile:
        results = core.parse_listfile(tfile)

    assert results[0] == os.path.expandvars("$HOME/foo")


class TestGetConfig(utils.TestWithEnvClean):
    CONF_FILE = textwrap.dedent("""
    [nose-test]
    ; a section for testing behavior
    dir = foo
    """)

    def __unset_config(self):
        self.defer(_reset_piglit_config)
        self.add_teardown('XDG_CONFIG_HOME')
        self.add_teardown('HOME')

    def __move_local(self):
        """ Move a local piglit.conf so it isn't overwritten """
        if os.path.exists('piglit.conf'):
            shutil.move('piglit.conf', 'piglit.conf.restore')
            self.defer(shutil.move, 'piglit.conf.restore', 'piglit.conf')

    def setup(self):
        self.__unset_config()
        self.__move_local()

    def test_xdg_config_home(self):
        """ get_config() finds $XDG_CONFIG_HOME/piglit.conf """
        with utils.tempdir() as tdir:
            os.environ['XDG_CONFIG_HOME'] = tdir
            with open(os.path.join(tdir, 'piglit.conf'), 'w') as f:
                f.write(TestGetConfig.CONF_FILE)
            core.get_config()

        nt.ok_(core.PIGLIT_CONFIG.has_section('nose-test'),
               msg='$XDG_CONFIG_HOME not found')

    def test_config_home_fallback(self):
        """ get_config() finds $HOME/.config/piglit.conf """
        with utils.tempdir() as tdir:
            os.environ['HOME'] = tdir
            os.mkdir(os.path.join(tdir, '.config'))
            with open(os.path.join(tdir, '.config/piglit.conf'), 'w') as f:
                f.write(TestGetConfig.CONF_FILE)
            core.get_config()

        nt.ok_(core.PIGLIT_CONFIG.has_section('nose-test'),
               msg='$HOME/.config/piglit.conf not found')

    def test_local(self):
        """ get_config() finds ./piglit.conf """
        with utils.tempdir() as tdir:
            self.defer(os.chdir, os.getcwd())
            os.chdir(tdir)

            with open(os.path.join(tdir, 'piglit.conf'), 'w') as f:
                f.write(TestGetConfig.CONF_FILE)

            core.get_config()

        nt.ok_(core.PIGLIT_CONFIG.has_section('nose-test'),
               msg='./piglit.conf not found')

    def test_piglit_root(self):
        """ get_config() finds "piglit root"/piglit.conf """
        with open('piglit.conf', 'w') as f:
            f.write(TestGetConfig.CONF_FILE)
        self.defer(os.unlink, 'piglit.conf')
        self.defer(os.chdir, os.getcwd())
        os.chdir('..')

        core.get_config()

        nt.ok_(core.PIGLIT_CONFIG.has_section('nose-test'),
               msg='$PIGLIT_ROOT not found')
