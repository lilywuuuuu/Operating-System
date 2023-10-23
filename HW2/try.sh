g++ hw2.cpp -o hw2

correct_count=0
total_cases=1000
for ((i=1; i<=total_cases; i++)) do
    input_file="mytestcase/testcase/tc_${i}.txt"
    answer_file="mytestcase/ans/ans_${i}.txt"
    ./hw2 < "$input_file" > output.txt

    if diff -w output.txt "$answer_file" >/dev/null; then
        echo "Testcase ${i} passed."
        correct_count=$((correct_count + 1))
    else
        echo "Testcase ${i} failed."
    fi
done

rm output.txt
echo ${correct_count} correct out of ${total_cases}


