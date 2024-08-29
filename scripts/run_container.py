import subprocess
import shlex

command = 'docker run --name c-databases-cont --rm c-databases-img'
subprocess.run(shlex.split(command), check=True)
