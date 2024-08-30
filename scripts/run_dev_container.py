import subprocess

command = 'docker run --name c-databases-cont -it --rm c-databases-img bash'
subprocess.run(command, shell=True, check=True)
