import subprocess
import utils

script = utils.SCRIPTS_DIR / 'build_docker_image.py'
command = f'{utils.PYTHON_EXECUTABLE} {script}'
subprocess.run(command, shell=True, check=True)

command = 'docker run --name c-databases-cont --rm c-databases-img'
subprocess.run(command, shell=True, check=True)
