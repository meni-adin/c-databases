import os
import subprocess
import shlex
import utils
from pathlib import Path

CLANG_FORMAT_CFG = utils.WORKING_DIR/'clang_format.yml'

directories = [
    utils.WORKING_DIR/'src',
    utils.WORKING_DIR/'test',
]

c_cpp_files = []
for directory in directories:
    c_cpp_files.extend(directory.rglob("*.c"))
    c_cpp_files.extend(directory.rglob("*.h"))
    c_cpp_files.extend(directory.rglob("*.cpp"))
    c_cpp_files.extend(directory.rglob("*.hpp"))

for file in c_cpp_files:
    print(f'Running clang-format on {file}')
    command = f'clang-format-17 -style=file:{CLANG_FORMAT_CFG} -i {file}'
    subprocess.run(shlex.split(command), check=True)
