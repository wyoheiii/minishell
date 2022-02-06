#!/bin/bash

cd "$(dirname $0)"

readonly SCRIPT_DIR="$(pwd)"
readonly TMP_DIR="${SCRIPT_DIR}/tmp"

readonly CASES_DIR="${SCRIPT_DIR}/cases"

readonly MINISHELL_STDOUT_FILE="${TMP_DIR}/minishell_stdout.txt"
readonly MINISHELL_STDOUT_BACKUP="${TMP_DIR}/minishell_stdout.txt-e"
readonly MINISHELL_STDERR_FILE="${TMP_DIR}/minishell_stderr.txt"
readonly MINISHELL_STATUS_FILE="${TMP_DIR}/minishell_status.txt"
readonly BASH_STDOUT_FILE="${TMP_DIR}/bash_stdout.txt"
readonly BASH_STDERR_FILE="${TMP_DIR}/bash_stderr.txt"
readonly BASH_STATUS_FILE="${TMP_DIR}/bash_status.txt"

readonly LOG_FILE="${SCRIPT_DIR}/${LOG_FILE_NAME}"

readonly COLOR_RESET="\033[0m"
readonly COLOR_GREEN="\033[32m"
readonly COLOR_RED="\033[31m"

result_all=0
result_ok=0
result_ko=0
