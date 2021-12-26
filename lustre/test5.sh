#! /bin/bash

# setstripe to PFL without pool to dir without PFL but with pool

rm -rf  /mnt/lustre/*

red=$(tput setaf 1)
reset=$(tput sgr0)
bold=$(tput bold)
warn()
{
    echo "${bold}${red}$@${reset}"
}

create_pool()
{
	echo
	echo create pool $1
	echo

	lctl pool_new lustre.$1
	lctl pool_add lustre.$1 OST0000
	lfs pool_list lustre
}

destroy_pool()
{
	echo
	echo destroy pool..
	echo

	lctl pool_remove lustre.$1 OST0000
	lctl pool_destroy lustre.$1
	lfs pool_list lustre
}

create_pool pool1

mkdir /mnt/lustre/dir
lfs setstripe -p pool1 /mnt/lustre/dir
warn "after setstripe -p"
/home/vs/alg/lustre/xattr /mnt/lustre/dir

lfs setstripe -c 2 /mnt/lustre/dir
warn "after setstripe -c 2"
/home/vs/alg/lustre/xattr /mnt/lustre/dir

lfs setstripe -E 1M -L mdt -E -1 -c 2 /mnt/lustre/dir

warn "after setstripe PFL with mdt"
/home/vs/alg/lustre/xattr /mnt/lustre/dir

lfs setstripe -E 1M -c 1 -i 0 -E -E -1 -c 2 /mnt/lustre/dir
warn "after setstripe PFL without mdt"
/home/vs/alg/lustre/xattr /mnt/lustre/dir

destroy_pool pool1



