#!/bin/sh
#
echo "Generating ssh keys"
[ ! -f /etc/ssh/ssh_host_rsa_key ] && ssh-keygen -A
echo "Creating .ssh dir"
mkdir -p /root/.ssh
echo "Inserting public ssh-key"
echo "super_secret_public_ssh_key" >> /root/.ssh/authorized_keys
chmod 700 /root/.ssh
chmod 600 /root/.ssh/authorized_keys
echo "Starting sshd"
/usr/sbin/sshd
echo "Finished"
tail -f /dev/null
