#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string.h>
#include <unistd.h>
#include <nss.h>
#include <pwd.h>
#include <grp.h>

#if HAVE_VAR_ATTRIBUTE_UNUSED
#  define _unused_ __attribute__((unused))
#else
#  define _unused_
#endif

enum nss_status _nss_me_getpwnam_r(const char *name,
                                   struct passwd *pwd,
                                   char *buffer _unused_, size_t buflen _unused_,
                                   int *errnop)
{
    if (strcmp(name, "me") != 0) {
        *errnop = 0;
        return NSS_STATUS_NOTFOUND;
    }

    pwd->pw_name   = "me";
    pwd->pw_passwd = "x";
    pwd->pw_uid    = getuid();
    pwd->pw_gid    = getgid();
    pwd->pw_gecos  = "Me";
    pwd->pw_dir    = "/home/me";
    pwd->pw_shell  = "/bin/sh";

    *errnop = 0;
    return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_me_getpwuid_r(uid_t uid,
                                   struct passwd *pwd,
                                   char *buffer _unused_, size_t buflen _unused_,
                                   int *errnop)
{
    if (uid != getuid()) {
        *errnop = 0;
        return NSS_STATUS_NOTFOUND;
    }

    pwd->pw_name   = "me";
    pwd->pw_passwd = "x";
    pwd->pw_uid    = getuid();
    pwd->pw_gid    = getgid();
    pwd->pw_gecos  = "Me";
    pwd->pw_dir    = "/home/me";
    pwd->pw_shell  = "/bin/sh";

    *errnop = 0;
    return NSS_STATUS_SUCCESS;
}

static char *empty_mem[] = { NULL };

enum nss_status _nss_me_getgrnam_r(const char *name,
                                   struct group *gr,
                                   char *buffer _unused_, size_t buflen _unused_,
                                   int *errnop)
{
    if (strcmp(name, "me") != 0) {
        *errnop = 0;
        return NSS_STATUS_NOTFOUND;
    }

    gr->gr_name = "me";
    gr->gr_gid  = getgid();
    gr->gr_passwd = "x";
    gr->gr_mem = empty_mem;

    *errnop = 0;
    return NSS_STATUS_SUCCESS;
}

enum nss_status _nss_me_getgrgid_r(gid_t gid,
                                   struct group *gr,
                                   char *buffer _unused_, size_t buflen _unused_,
                                   int *errnop)
{
    gid_t my_gid = getgid();

    if (gid != my_gid) {
        *errnop = 0;
        return NSS_STATUS_NOTFOUND;
    }

    gr->gr_name = "me";
    gr->gr_gid  = getgid();
    gr->gr_passwd = "x";
    gr->gr_mem = empty_mem;

    *errnop = 0;
    return NSS_STATUS_SUCCESS;
}
