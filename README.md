# nss\_me

[![Build Status](https://travis-ci.org/L3n41c/nss_me.svg?branch=master)](https://travis-ci.org/L3n41c/nss_me)

## Description

`nss-me` is a plug-in module for the GNU Name Service Switch (NSS) functionality of the GNU C Library (glibc) that always resolves the user and group of the caller. Whatever the uid and gid of the caller is, this module will return the “`me`” user and group.

It was designed to provide user and group resolution in context where a process runs with unknown uid/gid and requires their resolution.

Typical example is a docker container which can be started with `docker run -u <any_uid>:<any_gid> …` even if the `<any_uid>:<any_gid>` doesn’t exist in the `/etc/passwd` of the docker image.

To activate the NSS module, add “`me`” to the lines starting with “`passwd:`” and “`group:`” in `/etc/nsswitch.conf`.

It is recommended to place “`me`” at the end of the lines in order to privilege any other resolver and use “`me`” only as last resort.

## Example

Here is an example `/etc/nsswitch.conf` file that enables `nss_me` correctly:

```
passwd: compat mymachines systemd me
group: compat mymachines systemd me
shadow: compat

publickey: files

hosts: files mymachines resolve [!UNAVAIL=return] dns myhostname
networks: files

protocols: files
services: files
ethers: files
rpc: files

netgroup: files
```

### Demo

Here is how a docker container behaves without `nss_me`:

```
[root@demo ~]# docker run -ti --rm -u 1002:1001 without_me /bin/bash
bash-4.3$ PS1="[\u@\h \W]\$ "
[I have no name!@96d6c1185fab /]$ id
uid=1002 gid=1001 groups=1001
[I have no name!@96d6c1185fab /]$ ssh example.org
No user exists for uid 1002
```

Here is how a docker container behaves with `nss_me`:

```
[root@demo ~]# docker run -ti --rm -u 1002:1001 with_me /bin/bash
bash-4.3$ PS1="[\u@\h \W]\$ "
[me@ff324856289c /]$ id
uid=1002(me) gid=1001(me) groups=1001(me)
[me@ff324856289c /]$ ssh example.org
ssh: connect to host example.org port 22: Network is unreachable
```

Thanks to `nss_me`, `ssh` is now accepting to work.
