import os

flags = [
    '-Wall',
    '-Wextra',
    '-x',
    'c++',
    '-std=c++14',
    '-DMILK_BUILD'
]

include_dirs = [
    'include'
]

for dir in include_dirs:
    flags.append('-I')
    flags.append(os.path.abspath(dir))

def FlagsForFile(filename):
  return {
    'flags': flags,
    'do_cache': True
  }
