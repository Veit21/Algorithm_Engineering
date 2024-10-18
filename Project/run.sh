#!/bin/bash

# define some variables
PREFERENCES_PATH="./config/preferences.json"

# make sure the output folder exists
mkdir -p ./data/output

# run the visualization script depending on OS
if [[ "$OSTYPE" == "darwin"* || "$OS" == "Darwin"* ]]; then

  # run the binary
  ./build/simulated_annealing --preferences $PREFERENCES_PATH
  python ./src/visualization.py $PREFERENCES_PATH
elif [[ "$OSTYPE" == "linux-gnu"* || "$OS" == "Linux"* ]]; then

  # run the binary
  ./build/simulated_annealing --preferences $PREFERENCES_PATH
  python3 ./src/visualization.py $PREFERENCES_PATH
elif [[ "$OSTYPE" == "msys"* || "$OS" == "Windows_NT"* ]]; then

  # run the binary
  ./build/simulated_annealing.exe --preferences $PREFERENCES_PATH
  python ./src/visualization.py $PREFERENCES_PATH
else
  echo "OS not found!"
fi