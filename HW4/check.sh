#!/usr/bin/bash

g++ 4-1.cpp -o 4-1
g++ 4-2_LRU.cpp -o LRU
g++ 4-2_LFU.cpp -o LFU

# if [ ! $# -eq 5 ]; then
#     echo "Usage: ./check.sh <part1_executable> <part2_LRU_executable> <part2_LFU_executable> <testcaseDir> <ansDir>"
#     exit 1
# fi
part1_executable="4-1"
part2_LRU_executable="LRU"
part2_LFU_executable="LFU"
testcaseDir="mytester/mytestcase"
ansDir="mytester/myans"

tmpfile="${ansDir}/tmp.txt"
touch $tmpfile

if [ ! -d "${ansDir}" ]; then
    echo "Error: ${ansDir} does not exist"
    exit 1
fi
if [ ! -d "${testcaseDir}" ]; then
    echo "Error: ${testcaseDir} does not exist"
    exit 1
fi

failed=0
for i in {0..999}
do
    filename="${testcaseDir}/part1/tc_${i}.txt"
    ./$part1_executable < $filename > $tmpfile
    diff $tmpfile "${ansDir}/part1/ans_${i}.txt" > /dev/null
    if [ $? -eq 0 ]; then
        # color it green
        echo "\033[32m part1 testcase ${i} passed \033[0m"
    else
        # color it red
        echo "\033[31m part1 testcase ${i} failed \033[0m"
        failed=1
    fi
done    
echo "part1 testcases finished, passed: $((1000-failed)), failed: $failed"

failed=0
for i in {0..999}
do
    filename="${testcaseDir}/part2/tc_${i}.txt"
    ./$part2_LRU_executable < $filename > $tmpfile
    diff $tmpfile "${ansDir}/part2_LRU/ans_${i}.txt" > /dev/null
    if [ $? -eq 0 ]; then
        # color it green
        echo "\033[32m part2_LRU testcase ${i} passed \033[0m"
    else
        # color it red
        echo "\033[31m part2_LRU testcase ${i} failed \033[0m"
        failed=1
    fi
done
echo "part2_LRU testcases finished, passed: $((1000-failed)), failed: $failed"

failed=0
for i in {0..999}
do
    filename="${testcaseDir}/part2/tc_${i}.txt"
    ./$part2_LFU_executable < $filename > $tmpfile
    diff $tmpfile "${ansDir}/part2_LFU/ans_${i}.txt" > /dev/null
    if [ $? -eq 0 ]; then
        # color it green
        echo "\033[32m part2_LFU testcase ${i} passed \033[0m"
    else
        # color it red
        echo "\033[31m part2_LFU testcase ${i} failed \033[0m"
        failed=1
    fi
done
echo "part2_LFU testcases finished, passed: $((1000-failed)), failed: $failed"

rm 4-1 LFU LRU