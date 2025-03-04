#!/bin/bash
# hex2ascii_pipe.sh: Read input from STDIN, extract hex tokens, and convert them to ASCII.

# Read all input from STDIN.
input=$(cat)

# Use grep to extract all hexadecimal tokens (words with hex digits only).
# Adjust the regex if needed.
hex_tokens=$(echo "$input" | grep -oE '[0-9a-fA-F]+')

# For each hex token, convert every two hex digits to a character.
for token in $hex_tokens; do
    # Remove any potential newline characters
    token=$(echo "$token" | tr -d '\n')
    # Insert \x before every two hex digits.
    formatted=$(echo "$token" | sed 's/../\\x&/g')
    # Use printf to interpret the escape sequences and print the ASCII characters.
    ascii=$(printf "%b" "$formatted")
    printf "%s " "$ascii"
done

printf "\n"
