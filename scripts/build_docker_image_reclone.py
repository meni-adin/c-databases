from datetime import datetime
import subprocess
import utils

command = f'docker build --build-arg CACHEBUST="{datetime.now()}" -t {utils.REPO_NAME}-img {utils.PROJECT_DIR}'
subprocess.run(command, shell=True, check=True)
