#!/bin/bash
if [ $UID != 0 ] ; then
	echo "must be called as superuser"
	exit 1
fi

SYSD_DIR=/etc/systemd/system

systemctl stop a.service
rm -rf $SYSD_DIR/a.service  

systemctl daemon-reload

