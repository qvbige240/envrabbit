#!/bin/bash
LIB_NAME=envcc
str_version="2.01"

function usge_exit()
{                                                                                                                                                                                    
        echo "  Usge: $0 platform [rebuild]"
        echo "  platform list:"
        echo -e "\033[32m               GEN3 \033[0m"
        echo -e "\033[32m               EX3 \033[0m"
        exit -1
}   

function _find_prj_path()
{
    if [ -d "`pwd`/../$1" ]; then
        echo "`pwd`/../$1"
    elif [ -d "`pwd`/../../$1/workspace" ]; then
        echo "`pwd`/../../$1/workspace"
    else
        echo "$1 not exsit: `pwd`/../$1 OR `pwd`/../../$1/workspace"
	exit -1
    fi
}

function init_etc()
{
    etc_profile="Resources/etc.profile"
    if [ -f ${etc_profile} ]; then
        . ${etc_profile}
        if [ "${game_version}a" == "a" ]; then
            echo "Did you forgot define 'game_version' into etc.profile"
        else
            str_version=${game_version}
        fi
        GAME_TYPE=${game_type}; echo "$GAME_TYPE"
    fi
}

function init_premake()
{
    dir_current=`pwd` #game's root
    prj_premake="premake"
    dir_premake=
    init_etc

    dir_premake=$(_find_prj_path ${prj_premake})
    . ${dir_premake}/premake_init.sh
    init_premake
    init_platform $1
}

if [ ! -n "$1" ]; then 
    usge_exit
fi

init_premake $1
automake_make ${dir_current} $str_version $2





