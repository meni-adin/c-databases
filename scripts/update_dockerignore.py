import utils
import shutil

SOURCE = utils.PROJECT_DIR/'.gitignore'
DESTINATION = utils.PROJECT_DIR/'.dockerignore'
shutil.copy(SOURCE, DESTINATION)
