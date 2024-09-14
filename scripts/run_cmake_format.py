import utils

CMAKE_FORMAT_CFG_PATH = utils.CONFIGURATIONS_DIR/'.cmake-format.py'

directories = [
    utils.PROJECT_DIR/'cmake',
    utils.PROJECT_DIR/'src',
    utils.PROJECT_DIR/'test',
]

cmake_files = []
cmake_files.append(utils.PROJECT_DIR/'CMakeLists.txt')
for directory in directories:
    cmake_files.extend(directory.rglob("CMakeLists.txt"))
    cmake_files.extend(directory.rglob("*.cmake"))

for file in cmake_files:
    print(f'Running cmake-format on {file}')
    command = f'cmake-format --config-file={CMAKE_FORMAT_CFG_PATH} -i {file}'
    utils.run_command(command, shell=True, check=True)
