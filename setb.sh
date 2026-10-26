#!/bin/bash
# Set B: Employee Commission Tracker

read -r -p "Enter Employee ID: " emp_id
read -r -p "Enter Total Sales Amount: " sales

# validation (optional — সময় কম হলে বাদ দিতে পারো)
if ! [[ $sales =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
    echo "Invalid sales amount"
    exit 1
fi

# tier অনুযায়ী rate
if [ "$(echo "$sales <= 5000" | bc)" -eq 1 ]; then
    rate=0
elif [ "$(echo "$sales <= 15000" | bc)" -eq 1 ]; then
    rate=10
else
    rate=15
fi

commission=$(echo "scale=4; $sales * $rate / 100" | bc)

# commission > 0 হলে 2.5% processing fee
if [ "$(echo "$commission > 0" | bc)" -eq 1 ]; then
    fee=$(echo "scale=4; $commission * 2.5 / 100" | bc)
else
    fee=0
fi

net=$(echo "scale=4; $commission - $fee" | bc)

echo "------------------------------------"
echo "Employee ID      : $emp_id"
printf 'Total Sales      : $%.2f\n' "$sales"
echo "Commission Rate  : $rate%"
printf 'Gross Commission : $%.2f\n' "$commission"
printf 'Processing Fee   : $%.2f\n' "$fee"
printf 'Net Commission   : $%.2f\n' "$net"
echo "------------------------------------"