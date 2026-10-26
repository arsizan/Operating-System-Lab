#!/bin/bash
# Set C: Student Scholarship Evaluator

read -r -p "Enter Student Name: " name
read -r -p "Enter GPA (out of 4.0): " gpa

# validation (optional — সময় কম হলে বাদ দিতে পারো)
if ! [[ $gpa =~ ^[0-9]+(\.[0-9]+)?$ ]] || [ "$(echo "$gpa > 4.0" | bc)" -eq 1 ]; then
    echo "Invalid GPA (must be between 0.0 and 4.0)"
    exit 1
fi

# tier অনুযায়ী base scholarship + bonus
if [ "$(echo "$gpa >= 3.5" | bc)" -eq 1 ]; then
    base=2000
    bonus=$(echo "scale=2; $base * 12.5 / 100" | bc)
elif [ "$(echo "$gpa >= 3.0" | bc)" -eq 1 ]; then
    base=1000
    bonus=0
else
    base=0
    bonus=0
fi

total=$(echo "scale=2; $base + $bonus" | bc)

echo "------------------------------------"
echo "Student Name      : $name"
echo "GPA               : $gpa"
printf 'Base Scholarship  : $%.2f\n' "$base"
printf 'Resource Bonus    : $%.2f\n' "$bonus"
printf 'Final Scholarship : $%.2f\n' "$total"
echo "------------------------------------"