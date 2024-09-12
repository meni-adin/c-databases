from pathlib import Path
import subprocess
import sys

PROJECT_DIR = Path(__file__).parent.parent.resolve()
SCRIPTS_DIR = PROJECT_DIR/'scripts'
PYTHON_EXECUTABLE = sys.executable
REPO_NAME = PROJECT_DIR.name

def program_available(program):
    command = f'{program} --version'
    result = subprocess.run(command, shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return result.returncode == 0

def run_command(command, **kwargs):
    print(f'Running command: {command}')
    result = subprocess.run(command, **kwargs)
    return result