#!/bin/bash
set -euo pipefail

get_day() {
  local day=$(date '+%-d')
  echo $day
}

get_month() {
  local month=$(date '+%m')
  echo $month
}

get_year() {
  local year=$(date '+%Y')
  echo $year
}

setup_day() {
  local day=$1
  local path="Day $day"

  echo "Setup directory for $path"
  
  if [[ -e "$path" ]]; then 
    echo "$path folder already exists"
  else
    mkdir "$path"
  fi
  
  if [[ -e "$path/Makefile" ]]; then
    echo "$path Makefile already exists"
  else
    cp "utils/Makefile" "$path/Makefile"
  fi
  
  if [[ -e "$path/solution.c" ]]; then
    echo "$path solution already exists"
  else
    cp "utils/template.c" "$path/solution.c"
  fi

  # Touch to create files as it won't overwrite files if already existing
  touch "$path/input.txt"

  cd "$path"
}

if [[ $# == 1 ]]; then
  setup_day $1
else
  if [[ $(get_month) != "12" || $(get_year) != "2025" ]]; then
    echo "Advent of Code 2025 has ended, use ./setup.sh {day} to setup a specific days directory."
  else 
    setup_day $(get_day)
  fi
fi
