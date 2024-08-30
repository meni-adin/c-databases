import subprocess
import utils

command = f'docker build -t c-databases-img {utils.WORKING_DIR}'
subprocess.run(command, shell=True, check=True)
