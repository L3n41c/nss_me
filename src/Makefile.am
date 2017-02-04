lib_LTLIBRARIES = libnss_me.la

libnss_me_la_SOURCES = \
	nss-me.sym \
	nss-me.c

libnss_me_la_LDFLAGS = \
	$(AM_LDFLAGS) \
	-module \
	-export-dynamic \
	-avoid-version \
	-shared \
	-shrext .so.2 \
	-Wl,--version-script=$(top_srcdir)/src/nss-me.sym
