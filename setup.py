from distutils.core import setup, Extension
import distutils.sysconfig

import imp

import git

r = git.Repo()

version = '"'+r.git.describe('--tags')+'"'

m = Extension('bar',
              define_macros = [('VERSION_STRING', version)],
              include_dirs = [imp.find_module('numpy')[1]+'/core/include'],
              sources = ['src/foo.cxx', 'src/bar.cxx'])

setup(name='bar',
      version = version,
      ext_modules = [m])
