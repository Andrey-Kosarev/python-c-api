import os
import shutil
from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as _build_ext

class build_ext(_build_ext):
    def run(self):
        # Run the original build_ext command
        _build_ext.run(self)
        # Remove the build directory after building the extension
        build_dir = os.path.join(os.getcwd(), 'build')
        if os.path.isdir(build_dir):
            shutil.rmtree(build_dir)

module = Extension(
    'hello_c_api',
    sources=['hello_c_api.cpp'],
    include_dirs=['C:/Program Files/Python311/include'],
    library_dirs=['C:/Program Files/Python311/libs'],
    #libraries=['python39']
)

setup(name='hello_c_api',
      version='1.0',
      description='Example module that says hello',
      ext_modules=[module])