#!/bin/bash

cp txttmp txt

./r &

usleep 7000
rm txt -f
