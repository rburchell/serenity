#!/bin/sh
set -e
rm trace.log || true
echo '[' >> trace.log
grep "{\"" run.log | perl -p -e "s/^[^{]*{\"/{\"/" >> trace.log
truncate -s-2 trace.log # newline and trailing ,
echo "" >> trace.log # add a new newline
mv trace.log ~
