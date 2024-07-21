from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as _build_ext


module = Extension(
    'mini_numpy',
    sources=['mini_numpy.cpp'] 
)

setup(name='mini_numpy',
      version='1.0',
      description='Example module that says hello',
      ext_modules=[module])