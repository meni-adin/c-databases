import subprocess
import shlex
import utils

command = f'docker build -t c-databases-img {utils.WORKING_DIR}'
subprocess.run(shlex.split(command), check=True)
