import subprocess
import shlex

command = 'docker run --name c-databases-cont -it --rm c-databases-img bash'
subprocess.run(shlex.split(command), check=True)
