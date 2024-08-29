import subprocess
import shlex
import utils
import shutil
import os

source = os.path.join(utils.WORKING_DIR, '.gitignore')
destination = os.path.join(utils.WORKING_DIR, '.dockerignore')
shutil.copy(source, destination)
# command = f'cat {utils.WORKING_DIR}/'
# subprocess.run(shlex.split(command), check=True)
