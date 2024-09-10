import argparse
import json
import subprocess
import utils

BUILD_TYPES = ['debug', 'release']

parser = argparse.ArgumentParser(description='Build and test C/C++ code')
parser.add_argument('-b', '--build-type', type=str, choices=BUILD_TYPES, help='Type of the build', default=None)
args = parser.parse_args()

if args.build_type:
    requested_build_types = [args.build_type]
else:
    requested_build_types = BUILD_TYPES

print(f'{requested_build_types=:}\n')

for build_type in requested_build_types:
    command = f'cmake --preset config-{build_type}'
    subprocess.run(command, shell=True, check=True)

    command = f'cmake --build --preset build-{build_type}'
    subprocess.run(command, shell=True, check=True)

    command = f'ctest --preset test-{build_type}'
    subprocess.run(command, shell=True, check=True)

    if(utils.program_available('valgrind')):
        command = f'ctest --preset test-{build_type} --show-only=json-v1'
        result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, text=True)

        tests_json = json.loads(result.stdout)
        tests = tests_json.get('tests', [])
        tests_executables_dict = {}  # Using dictionary and not set as iterating it preserves insertion order
        for test in tests:
            command = test.get('command', [])
            if command:
                tests_executables_dict[command[0]] = None
            else:
                print(f"No commands found for test {test.get('name')}")
                exit(1)
        for key in tests_executables_dict:
            command = f'valgrind --error-exitcode=1 --leak-check=full {key}'
            result = subprocess.run(command, shell=True, check=True)

    if(utils.program_available('clang-tidy')):
        compilation_database_path = utils.PROJECT_DIR/'build'/build_type/'compile_commands.json'
        script = utils.SCRIPTS_DIR/'run_clang_tidy.py'
        command = f'{utils.PYTHON_EXECUTABLE} {script} -d {compilation_database_path} -e'
        result = subprocess.run(command, shell=True, check=True)
