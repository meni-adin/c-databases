import subprocess

command = 'docker run --name c-databases-cont --rm c-databases-img'
subprocess.run(command, shell=True, check=True)
