./autogen.sh
./configure
make maintainer-clean || true
rm -f aclocal.m4 compile config.h.in   configure ltmain.sh Makefile.in  ar-lib *~ 
rm -f install-sh missing config.guess  config.sub depcomp 
rm -Rf config

