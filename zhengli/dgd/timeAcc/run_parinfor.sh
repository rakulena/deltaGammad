#!/bin/bash

if [ $# -ne 1 ]; then
   echo param error!
   exit 1
fi

MODE="$1"
TARGET_DIR="~/dgd/timeAcc"
RENAME_DIR="~/dgd/timeAcc"

if [ "$MODE" == "ks" ]; then
   
    TARGET_MODE_DIR="${TARGET_DIR}/jpsiks"
    
    mkdir -p "${TARGET_MODE_DIR}"
    
    cp -r "${TARGET_DIR}/output" "${TARGET_MODE_DIR}/" 2>/dev/null && echo "  - output complete" || echo "  - output fail"
    cp -r "${TARGET_DIR}/parinfor" "${TARGET_MODE_DIR}/" 2>/dev/null && echo "  - parinfor complete" || echo "  - parinfor fail"
    
    echo "jpsiks complete"
    
elif [ "$MODE" == "kst" ]; then

    TARGET_MODE_DIR="${TARGET_DIR}/jpsikst"
    
    mkdir -p "${TARGET_MODE_DIR}"
    
    cp -r "${TARGET_DIR}/output" "${TARGET_MODE_DIR}/" 2>/dev/null && echo "  - output complete" || echo "  - output fail"
    cp -r "${TARGET_DIR}/parinfor" "${TARGET_MODE_DIR}/" 2>/dev/null && echo "  - parinfor complete" || echo "  - parinfor fail"
    
    echo "jpsikst complete"
    
elif [ "$MODE" == "update" ]; then

    g++ -o "${RENAME_DIR}/update_parameters" "${RENAME_DIR}/update_parameters.cpp"
    
    if [ $? -eq 0 ]; then
        echo "success"
        chmod +x "${RENAME_DIR}/update_parameters" 2>/dev/null

        cd "${RENAME_DIR}" || exit 1
        ./update_parameters
      
        echo "update complete"
    else
        echo "fail,exit"
        exit 1
    fi
    
else
 
    exit 1
fi