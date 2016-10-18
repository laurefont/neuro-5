#!/bin/bash

#this will add the upstream branch (the main / team one)
git remote add upstream https://github.com/EPFL-SV-cpp-projects/neuro-5.git
git remote -v

#this will synchronize user's branch with the main on
git fetch upstream
git checkout master
git merge upstream/master
