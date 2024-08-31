import subprocess
import sys
from pathlib import Path

PROJECT_DIR = Path(__file__).parent.parent.resolve()
SCRIPTS_DIR = PROJECT_DIR / 'scripts'
PYTHON_EXECUTABLE = sys.executable

def program_available(program):
    command = f'{program} --version'
    result = subprocess.run(command, shell=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return result.returncode == 0
