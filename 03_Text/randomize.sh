#!/usr/bin/env dash

w=0
h=0
mw=$(tput cols)
mh=$(tput lines)
data="$(cat - | fold -w$mw | head -n$mh)"
dh=$((($(echo "$data" | wc -l) - 1) / 2 + 1))
dw=$((($(echo "$data" | while read line ; do echo "$line" | sed 's/./\0\n/g' | wc -l; done | sort -h | tail -n1) - 2) / 2 + 1))

exit_handler() {
	tput cnorm
	tput clear
	tput rmcup
}

tput smcup && tput civis
trap exit_handler EXIT
trap 'exit 127' INT HUP INT QUIT PIPE TERM

echo "$data" |
sed 's/./\0\n/g' |
while IFS= read c; do
	echo "$w $h $c"
	if test -z "$c"; then
		w=0
		h=$((h + 1))
	else
		w=$((w + 1))
	fi
done | shuf |
while read x y c; do
	if test -n "$c"; then
		# echo "'$((y + mh - dh))' '$((x + mw - dw))'"
		tput cup $((y + mh / 2 - dh)) $((x + mw / 2 - dw))
		echo -n "$c"
		sleep ${1:-0}
	fi
done

sleep 1
