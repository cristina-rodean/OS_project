#!/bin/bash

while read line
do
 echo $line | grep -E "^[A-Z].*[a-zA-Z0-9\.])*\." | grep -E "^[^\.]+\.$" | grep -v "and[ ]*," | grep -v n[pb]
done