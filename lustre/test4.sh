#! /bin/bash

rm -rf  /mnt/lustre/*

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
create_pool pool2

mkdir /mnt/lustre/dir
lfs setstripe -p pool1 /mnt/lustre/dir
/home/vs/alg/lustre/xattr /mnt/lustre/dir

lfs setstripe -E 1M -L mdt -E -1 -c 2 -p pool2 /mnt/lustre/dir

/home/vs/alg/lustre/xattr /mnt/lustre/dir


destroy_pool pool2
destroy_pool pool1



