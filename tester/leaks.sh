#!/bin/bash

#-------------------------------------
# USER SETTING
#-------------------------------------
readonly MINISHELL_DIR="../"
readonly MINISHELL_EXE="minishell_leaks"
readonly MINISHELL_PROMPT="$ "
#-------------------------------------

readonly MINISHELL_PATH="${MINISHELL_DIR}${MINISHELL_EXE}"
readonly LOG_FILE_NAME="leaks.log"

source help/helper.sh

rm -f "${TMP_DIR}/*" "${LOG_FILE}"

build_minishell_leaks () {
	make -C "${MINISHELL_DIR}" leaks
}

exec_minishell (){
	"${MINISHELL_PATH}"
}

clean_minishell_leaks () {
	make -C "${MINISHELL_DIR}" fcleanleaks
}

if [[ $1 == clean ]]; then
	clean_minishell_leaks
	exit
elif [[ -e ${MINISHELL_PATH} ]]; then
	echo "minishell_leaks exist!"
else
	build_minishell_leaks
fi

create_file () {
	mkdir ${TMP_DIR}
	mkdir a b
	printf '#!/bin/bash\necho a' > a/cmd
	printf '#!/bin/bash\necho b' > b/cmd
	printf '#!/bin/bash\necho cwd' > cmd
	printf '#!/bin/bash\necho 42' > exe
	printf '#include<unistd.h>\nint main(){write(1, "fd1\\n", 4);}' > rb.c
	chmod +x a/cmd b/cmd cmd exe
}


run_all_tests () {
	for file in $(ls ${CASES_DIR} | sed 's/\.txt//' | sed -e '/self/d'); do
		echo -e "\n\n---------------------------------"
		echo "${file}TEST"
		echo -e "---------------------------------"
		echo -e "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" >> ${LOG_FILE}
		echo "            ${file}TEST" >> ${LOG_FILE}
		echo -e "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n" >> ${LOG_FILE}
		run_tests "${file}"
	done
	print_result
}
run_tests () {
	while read -r line; do
		test_cmd="${line}\nexit"
		run_shell "$test_cmd" "${CASES_DIR}/$1.txt"
		check_diff "$test_cmd"
		output_log "$test_cmd"
	done < "${CASES_DIR}/$1.txt"
}
run_shell () {
	run_minishell "$test_cmd"
	clean
}

run_minishell () {
	echo -e "$1" | "${MINISHELL_PATH}" > ${MINISHELL_STDOUT_FILE} 2> /dev/null
	minishell_status=$?
	sed -i "" -e "/${MINISHELL_PROMPT}/d" ${MINISHELL_STDOUT_FILE}
}

check_diff () {
	if is_ok ; then
		print_ok
		let result_ok++
	else
		print_ko
		let result_ko++
	fi
	let result_all++
}

print_result () {
	echo -e "\n\n\nRESULT"
	if [[ ${result_ok} -eq ${result_all} ]]; then
		printf "\t${COLOR_GREEN}${result_ok} / ${result_all}${COLOR_RESET}\t\n"
	else
		printf "\t${COLOR_RED}${result_ok} / ${result_all}${COLOR_RESET}\t\n"
	fi
}

print_ok () {
	printf "${COLOR_GREEN}[✔ ]${COLOR_RESET}"
}

print_ko () {
	printf "${COLOR_RED}[✔ ]${COLOR_RESET}"
}

is_ok () {
	cat ${MINISHELL_STDOUT_FILE} | grep "0 leaks for 0 total leaked bytes." > /dev/null
	return $?
}

print_case () {
	echo -n "case: $1"
}

output_log () {
	echo -e "\n-------------------------" >> ${LOG_FILE}
	if is_ok ; then
		echo -n "[OK ] " >> ${LOG_FILE}
	else
		echo -n "[KO ] " >> ${LOG_FILE}
	fi
	echo $(print_case "$1") >> ${LOG_FILE}
	echo "-------------------------" >> ${LOG_FILE}
	cat ${MINISHELL_STDOUT_FILE} | grep "bytes" >> ${LOG_FILE}
}

clean () {
	find . -maxdepth 1 -type f | grep -v -E "cmd|test.sh|result.log|leaks.sh|${LOG_FILE_NAME}|exe|rb.c" | xargs rm
}

main () {
	create_file
	run_all_tests
	rm -rf "${TMP_DIR}"
	clean
	bash ./help/rmdir.sh
	rm -f ./cmd ./sym ./exe ./rb.c
}

main $@
