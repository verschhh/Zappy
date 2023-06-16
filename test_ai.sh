#!/bin/bash

commands=(
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n lol"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n mdr"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    "python3 ./zappy_ai -p 1235 -n pt"
    # Add more commands here
)

declare -a pids
declare -A exit_codes
declare -A count

for cmd in "${commands[@]}"; do
    exit_code_file=$(mktemp)
    gnome-terminal --disable-factory -- bash -c "$cmd; echo \$? > $exit_code_file" &
    pids+=($!)
    exit_codes[$exit_code_file]="PID $!"
done

for pid in "${pids[@]}"; do
    wait $pid
done

for exit_code_file in "${!exit_codes[@]}"; do
    exit_code=$(cat $exit_code_file)
    count[$exit_code]=$((count[$exit_code] + 1))
    rm $exit_code_file
done

echo "Exit codes:"
total=${#commands[@]}
for code in "${!count[@]}"; do
    percentage=$((count[$code] * 100 / total))
    echo "  $code: ${count[$code]} ($percentage%)"
done