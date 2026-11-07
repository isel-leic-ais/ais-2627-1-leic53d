#!/bin/bash

if [ $UID != 0 ] ; then
	echo "must be called as superuser"
	exit 1
fi

SYSD_DIR=/etc/systemd/system


cp a.service b.service  $SYSD_DIR 
systemctl daemon-reload



		
		
	
