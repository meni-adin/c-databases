import subprocess
import utils
import os

IGNORE = ['build', '.git',]

for item in os.listdir(utils.PROJECT_DIR):
    if item in IGNORE:
        continue

    print(f'Updating {item}')

    command = f'docker exec c-databases-cont rm -rf /root/{item}'
    subprocess.run(command, shell=True, check=True)

    item_full_path = utils.PROJECT_DIR / item
    command = f'docker cp {item_full_path} c-databases-cont:/root/'
    subprocess.run(command, shell=True, check=True)
