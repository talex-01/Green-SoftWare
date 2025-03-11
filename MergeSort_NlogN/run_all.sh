#!/bin/bash

# Executa o comando make measureInt
make measureInt
# Verifica se o arquivo measurements.csv existe e renomeia
if [ -f "measurements.csv" ]; then
    mv measurements.csv o2_int_1000000.csv
    echo "Arquivo renomeado para int_1000000.csv"
else
    echo "O arquivo measurements.csv não foi encontrado após measureInt."
fi

# Executa o comando make measureFloat
make measureFloat
# Verifica se o arquivo measurements.csv existe e renomeia
if [ -f "measurements.csv" ]; then
    mv measurements.csv o2_float_1000000.csv
    echo "Arquivo renomeado para float_1000000.csv"
else
    echo "O arquivo measurements.csv não foi encontrado após measureFloat."
fi

# Executa o comando make measureDouble
make measureDouble
# Verifica se o arquivo measurements.csv existe e renomeia
if [ -f "measurements.csv" ]; then
    mv measurements.csv o2_double_1000000.csv
    echo "Arquivo renomeado para double_1000000.csv"
else
    echo "O arquivo measurements.csv não foi encontrado após measureDouble."
fi

# Executa o comando make measureString
make measureString
# Verifica se o arquivo measurements.csv existe e renomeia
if [ -f "measurements.csv" ]; then
    mv measurements.csv o2_string_1000000.csv
    echo "Arquivo renomeado para string_1000000.csv"
else
    echo "O arquivo measurements.csv não foi encontrado após measureString."
fi
