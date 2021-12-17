#! /bin/bash

#
# this is to investigate the difference between
# lfs setstripe -p mypool /mnt/lustre/dir1
# lfs setstripe -E 1M -L mdt -E -1 -c 1 /mnt/lustre/dir1
# and
# lfs setstripe -E 1M -L mdt -E -1 -c 1 -p mypool /mnt/lustre/dir1
#
#

create_pool()
{
	echo
	echo create pool..
	echo

	lctl pool_new lustre.mypool
	lctl pool_add lustre.mypool OST0000
	lfs pool_list lustre
}

destroy_pool()
{
	echo
	echo destroy pool..
	echo

	lctl pool_remove lustre.mypool OST0000
	lctl pool_destroy lustre.mypool
	lfs pool_list lustre
}

rm -rf /mnt/lustre/*

lctl set_param debug=-1 debug_mb=256
create_pool

echo create dir
mkdir /mnt/lustre/dir1
/home/vs/soft/xattr /mnt/lustre/dir1
mkdir /mnt/lustre/dir2

echo add pool
lfs setstripe -p mypool /mnt/lustre/dir1
/home/vs/soft/xattr /mnt/lustre/dir1

echo add PFL
lfs setstripe -E 1M -L mdt -E -1 -c 1 /mnt/lustre/dir1
/home/vs/soft/xattr /mnt/lustre/dir1

echo add PFL with pool
lfs setstripe -E 1M -L mdt -E -1 -c 1 -p mypool /mnt/lustre/dir2
/home/vs/soft/xattr /mnt/lustre/dir2

destroy_pool

