import subprocess
import shlex
import utils
import os

IGNORE = ['build', '.git',]

for item in os.listdir(utils.WORKING_DIR):
    if item in IGNORE:
        continue
    print(f'Updating {item}')
    command = f'docker exec c-databases-cont rm -rf /root/{item}'
    subprocess.run(shlex.split(command), check=True)
    item_full_path = os.path.join(utils.WORKING_DIR, item)
    command = f'docker cp {item_full_path} c-databases-cont:/root/'
    subprocess.run(shlex.split(command), check=True)
