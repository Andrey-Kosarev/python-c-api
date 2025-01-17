from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as _build_ext


module = Extension(
    'hello_c_api',
    sources=['hello_c_api.cpp'],
    include_dirs=['C:/Program Files/Python311/include'],
    library_dirs=['C:/Program Files/Python311/libs'],
)

setup(name='hello_c_api',
      version='1.0',
      description='Example module that says hello',
      ext_modules=[module])