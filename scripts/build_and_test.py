import subprocess
import sys
import utils

BUILD_TYPES = ['debug', 'release']

for build_type in BUILD_TYPES:
    command = f'cmake --preset config-{build_type}'
    subprocess.run(command, shell=True, check=True)

    command = f'cmake --build --preset build-{build_type}'
    subprocess.run(command, shell=True, check=True)

    command = f'ctest --preset test-{build_type}'
    subprocess.run(command, shell=True, check=True)

    if(utils.program_available('valgrind')):
        valgrind_passed = False
        # command = f'valgrind ctest --preset test-{build_type}'
        command = f'valgrind build/{build_type}/test/doubly_linked_list_test/doubly_linked_list_test'
        print('original:', file=sys.stderr, flush=True)
        subprocess.run(command, shell=True, check=True)
        # result = subprocess.run(command, shell=True, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        # print('stdout:', file=sys.stderr)
        # for line in result.stdout.splitlines():
        #     print(line)
        #     if 'All heap blocks were freed -- no leaks are possible' in line:
        #         print('found in stdout')
        #         valgrind_passed = True
        # for line in result.stderr.splitlines():
        #     print(line)
        #     if 'All heap blocks were freed -- no leaks are possible' in line:
        #         print('found in stderr')
        #         valgrind_passed = True

        #     if ('All heap blocks were freed -- no leaks are possible' in line):
        #         valgrind_passed = True
        # if valgrind_passed:
        #     print('valgrind test passed')
        # else:
        #     print('valgrind test failed')
        #     exit(1)
