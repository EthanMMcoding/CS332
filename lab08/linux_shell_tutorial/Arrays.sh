#!/bin/bash
Name=("Alice" "Bob" "Charlie")
Name[3]="dave"
echo "Names are: " ${Name[*]}