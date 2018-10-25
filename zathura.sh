#!/bin/sh
#
# Based on tabbed-zathura script from:
#
#   http://taitran.ca/vim/latex/markdown/2015/03/11/vim-latex-and-markdown-preview-scripts.html

invoked_as="$0"
usage() {
    if [ "$#" -gt 0 ]; then
        printf "Error opening %s\n\n" "$*"
    fi

    printf "Usage: %s (-v) FILENAME\n\n" "$invoked_as"
    printf "\t-v\tRun verbosely.\n"
}
if ! hash xprop 2>/dev/null; then
    >&2 printf "%s requires xprop to be installed.\n" "$invoked_as"
    exit 1
fi

verbose=0
while getopts hv opt; do
    case $opt in
        h) usage
           exit 0
           ;;
        v) verbose=1 ;;
        *) >&2 usage
           exit 1
           ;;
    esac
done
shift "$((OPTIND - 1))"

xidfile="/tmp/tabbed-zathura.xid"

filename=
if [ "$#" -gt 0 ] && [ -f "$1" ]; then
    filename="$1"
else
    >&2 usage $*
    exit 1
fi

runtabbed() {
	tabbed -cdn tabbed-zathura -r 2 zathura -e '' --fork "$filename" \
        >"$xidfile" 2>/dev/null &
}

if [ ! -r "$xidfile" ]; then
    if [ $verbose -ne 0 ]; then
        >&2 printf "%s not found.\n" "$xidfile"
    fi
	runtabbed
else
	xid=$(<"$xidfile")
    if [ $verbose -ne 0 ]; then
        >&2 printf "xid=%s\n" $xid
    fi
    wm_class=
	xprop -id "$xid" >/dev/null 2>&1
	if [ $? -eq 0 ]; then
        wm_class=$(xprop -id "$xid" WM_CLASS | awk -F= '{print $2}' | awk -F, '{print $1}' | sed 's/["[:space:]]*//g')
    fi
    if [ x"$wm_class" = "xtabbed-zathura" ]; then
        if [ $verbose -ne 0 ]; then
            >&2 printf "Valid process with xid=%s found. Reparenting zathura to that process.\n" $xid
        fi
		zathura -e "$xid" --fork "$filename" >/dev/null 2>&1 &
    else
        if [ $verbose -ne 0 ]; then
            >&2 printf "Process with xid=%s not found or not valid.\n" $xid
        fi
		runtabbed
	fi
fi
