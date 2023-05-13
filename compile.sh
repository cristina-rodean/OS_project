#!/bin/bash

if [ $# -ne 1 ]; then
  echo "wrong number of arguments"
  exit 1
fi

filename=$(basename -- "$1")
filename="${filename%.*}"

output=$(gcc -Wall "$filename" "$1" 2>&1)

errorCnt=$(echo "$output" | grep -c "error:")
warningCnt=$(echo "$output" |grep -c "warning:")

echo "Number of errors: $errorCnt"
echo "Number of warnings: $warningCnt"