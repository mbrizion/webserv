#! /bin/bash
find srcs/ -name \*.cpp -print | cut -c6- | sort | tr '\n' ' '
