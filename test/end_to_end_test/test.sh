#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Not all required files was transferred"
    exit 1
fi

rbt="$1"
test_data="$2" 

if [ ! -d "$test_data" ]; then
    echo " $test_data not found"
    exit 1
fi

task_dir="$test_data""/tasks";

files=("$task_dir"/*.dat)

for file in "${files[@]}"; do 
    echo "-----------------------------------"
    s=${file##*/}; 
    echo Test name:  ${s%.dat};
    
    result=$( "$rbt" < "$file" )
    answ=$(cat "$test_data"/answers/${s%.dat}.ans);

    if [ "$result" == "$answ" ]; then
        echo "passed"
    else
        echo "faild"
        exit 1
    fi
    echo "-----------------------------------"
done