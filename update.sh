#!/bin/bash

cd `dirname "$0"`
git add .
git commit -m "Automatic Update"
git push origin master
doxygen Doxyfile
cd html/
git add .
git commit -m "Automatic Update"
git push origin gh-pages
exit 0
