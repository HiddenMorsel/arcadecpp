REP="${HOME}/${REPL_SLUG}"
mkdir -p ${REP}/.bin

SOURCE="https://raw.githubusercontent.com/senapk/tk/master/tk.py"
TARGET="${REP}/.bin/tk.py"
wget -nv ${SOURCE} -O ${TARGET}
cd ${REP}/.bin
ln -sf tk.py tk
cd -
chmod +x ${TARGET}

SOURCE="https://raw.githubusercontent.com/senapk/cppaux/master/fn.hpp"
TARGET="${REP}/.include/fn.hpp"
wget -nv ${SOURCE} -O ${TARGET}

