#!/bin/bash

rm combined.bin

# Make bootloader
cd bootloader
make clean
make

# Make application
cd ../application
make clean
make

# Define the start address of the application flash region
bootloader_flash_start=0x08000000
application_flash_start=0x08002000

# Binary file names
bootloader_file="gen_btld/stm32f103c8t6_btld.bin"
application_file="gen_app/stm32f103c8t6_app.bin"
combined_file="combined.bin"

# Calculate the required padding size
bootloader_size=$(wc -c < "$bootloader_file")
padding_size=$((application_flash_start - bootloader_size - bootloader_flash_start))

# Generate a padding binary file
padding_file=$(mktemp)
truncate -s $padding_size $padding_file

# Concatenate the bootloader binary, padding, and application binary
cat $bootloader_file $padding_file $application_file > $combined_file

# Clean up the temporary padding file
rm -f $padding_file