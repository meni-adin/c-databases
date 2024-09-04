import subprocess
import utils

command = f'docker build -t {utils.REPO_NAME}-img {utils.PROJECT_DIR}'
subprocess.run(command, shell=True, check=True)
