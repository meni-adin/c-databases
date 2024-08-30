import subprocess

BUILD_TYPES = ['debug', 'release']

for build_type in BUILD_TYPES:
    command = f'cmake --preset config-{build_type}'
    subprocess.run(command, shell=True, check=True)

    command = f'cmake --build --preset build-{build_type}'
    subprocess.run(command, shell=True, check=True)

    command = f'ctest --preset test-{build_type}'
    subprocess.run(command, shell=True, check=True)
