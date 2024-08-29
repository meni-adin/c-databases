import os
import subprocess
import shlex
import utils
import glob

SRC_DIR  = os.path.join(utils.WORKING_DIR, 'src')
TEST_DIR = os.path.join(utils.WORKING_DIR, 'test')
CLANG_FORMAT_CFG = os.path.join(utils.WORKING_DIR, 'clang_format.yml')

# command = f'find {SRC_DIR} {TEST_DIR} ' \
#           r'-type f ' \
#           r'\( -name "*.c" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) ' \
#           f'-exec clang-format -style=file:{CLANG_FORMAT_CFG} ' \
#           r'-i {} \;'
# subprocess.run(shlex.split(command), check=True)

directories = [SRC_DIR, TEST_DIR]
c_cpp_files = []
for directory in directories:
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".c") or file.endswith(".h") or file.endswith(".cpp") or file.endswith(".hpp"):
                c_cpp_files.append(os.path.join(root, file))

for file in c_cpp_files:
    print(f'Running clang-format on {file}')
    command = f'clang-format -style=file:{CLANG_FORMAT_CFG} -i {file}'
    subprocess.run(shlex.split(command), check=True)
