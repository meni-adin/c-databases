import subprocess
import utils

script = utils.SCRIPTS_DIR / 'build_docker_image.py'
command = f'{utils.PYTHON_EXECUTABLE} {script}'
subprocess.run(command, shell=True, check=True)

command = f'docker run --name {utils.REPO_NAME}-cont -it --rm {utils.REPO_NAME}-img bash'
subprocess.run(command, shell=True, check=True)
