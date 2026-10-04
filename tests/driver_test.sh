#!/bin/bash

DEVICE="/dev/mindbridge"

echo "================================="
echo " MindBridge Driver Test"
echo "================================="

if [ ! -e "$DEVICE" ]; then
    echo "[FAIL] $DEVICE does not exist."
    echo "Load the driver first using:"
    echo "sudo insmod driver/mindbridge.ko"
    exit 1
fi

echo "[PASS] Device found: $DEVICE"

echo "Mood: Test" | sudo tee "$DEVICE" > /dev/null

RESULT=$(sudo cat "$DEVICE")

echo "Driver returned:"
echo "$RESULT"

if [[ "$RESULT" == *"Mood: Test"* ]]; then
    echo "[PASS] Driver read/write test successful."
else
    echo "[FAIL] Driver read/write test failed."
    exit 1
fi

echo "================================="
echo " All driver tests completed."
echo "================================="
