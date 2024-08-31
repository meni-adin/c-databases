import subprocess
import utils
from datetime import datetime

command = f'docker build --build-arg CACHEBUST="{datetime.now()}" -t c-databases-img {utils.PROJECT_DIR}'
subprocess.run(command, shell=True, check=True)
