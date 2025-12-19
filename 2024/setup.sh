#!/bin/bash

# Function to create a new day directory
newDay() {
  if [ -z "$1" ]; then
    echo "Usage: newDay [day_number]"
    return 1
  fi

  DAY_DIR="day$1"
  if [ -d "$DAY_DIR" ]; then
    echo "Directory $DAY_DIR already exists!"
    return 1
  fi

  mkdir -p "$DAY_DIR"
  cp "helpers.h" "$DAY_DIR/helpers.h"
  cp "template.cpp" "$DAY_DIR/part1.cpp" 
  cp "template.cpp" "$DAY_DIR/part2.cpp"
  touch "$DAY_DIR/input1.txt" "$DAY_DIR/input2.txt"
  echo "Created $DAY_DIR with part1.cpp, part2.cpp, input1.txt, input2.txt."
}

# Function to compile a part
compile() {
  if [ -z "$1" ]; then
    echo "Usage: compile [file]"
    return 1
  fi

  FILE="$1"
  CPP_FILE="$FILE.cpp"
  OUTPUT="run_$FILE"

  if [ ! -f "$CPP_FILE" ]; then
    echo "File $CPP_FILE does not exist!"
    return 1
  fi

  clang++  -g -Wall -Wextra -std=c++20 -o "$OUTPUT" "$CPP_FILE"
}

# Function to run a part
run() {
  if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Usage: run [file] [input]"
    return 1
  fi

  FILE="$1"
  INPUT="$2.txt"
  EXEC="run_$FILE"

  if [ ! -f "$EXEC" ]; then
    echo "Executable $EXEC does not exist! Compile it first."
    return 1
  fi

  if [ ! -f "$INPUT" ]; then
    echo "Input file $INPUT does not exist!"
    return 1
  fi

  ./"$EXEC" < "$INPUT"
}

# Load functions into the shell
echo "Advent of Code environment loaded. Functions: newDay, compile, run"
