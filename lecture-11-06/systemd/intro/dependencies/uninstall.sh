#!/bin/bash

if [ $UID != 0 ] ; then
	echo "must be called as superuser"
	exit 1
fi

SYSD_DIR=/etc/systemd/system

rm -rf $SYSD_DIR/a.service $SYSD_DIR/b.service  


 
systemctl daemon-reload

