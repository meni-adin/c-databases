import subprocess
import utils

script = utils.SCRIPTS_DIR / 'build_docker_image.py'
command = f'{utils.PYTHON_EXECUTABLE} {script}'
subprocess.run(command, shell=True, check=True)

command = f'docker run --name {utils.REPO_NAME}-cont --rm {utils.REPO_NAME}-img'
subprocess.run(command, shell=True, check=True)
