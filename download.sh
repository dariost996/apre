#!/bin/bash

cd `dirname "$0"`
git pull origin master
cd html/
git pull origin gh-pages
exit 0
