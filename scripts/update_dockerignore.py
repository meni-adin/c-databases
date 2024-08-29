import utils
import shutil

SOURCE = utils.WORKING_DIR/'.gitignore'
DESTINATION = utils.WORKING_DIR/'.dockerignore'
shutil.copy(SOURCE, DESTINATION)
