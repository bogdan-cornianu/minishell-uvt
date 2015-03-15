# How-to compile #

## Get /src from the repository ##

**svn checkout http://minishell-uvt.googlecode.com/svn/ minishell-uvt-read-only**

## Install readline library (debian/ubuntu) ##

**sudo apt-get install libreadline5-dev**

## Run make ##

**make**

if not installed

**sudo apt-get install make**

## or ##

**gcc -lreadline -o minishell minishell.c**