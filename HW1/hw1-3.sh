#!/bin/bash

flag_path=false
# Read parent pid, child pid 
while [ "$#" -gt 0 ]; do
  case "$1" in
    --parent)
      parent="$2"
      shift 2
      ;;
    --child)
      child="$2"
      shift 2
      ;;
    --path)
      flag_path=true
      shift 1
      ;;
    *)
      echo "Unknown parameter passed: $1"
      exit 1
      ;;
  esac
done

# Check if parent or child is empty
if [ -z "$parent" ] || [ -z "$child" ]; then
  echo "Usage: $0 --parent PARENT_PID --child CHILD_PID [--path]"
  exit 1
fi

########
# TODO #
########

path+=("$child")

while [ "$child" -ne 1 ]; do
  # can't call it $PPID or else it will call the actuall ppid of the current running process
  ppid=$(ps -o ppid= -p $child) # find parent of child
  path+=("$ppid")
  if [ "$ppid" -eq "$parent" ]; then
    echo "Yes"
    # print path in reversed order with arrows
    if [ "$flag_path" = true ]; then
      # '#' = .size() '@' = all elements of array -> #path[@] = size of all items in array 'path'
      len=${#path[@]}
      for ((i=len-1; i>0; i--)); do
        echo -n ${path[$i]} # -n -> without newline
        echo -n " -> "
      done
      echo ${path[0]}
    fi
    exit 0
  fi
  child=$ppid
done
echo "No"

# The code below is only for demonstration purposes, please remove it before submitting.
# echo "parent pid: $parent, child pid: $child"
