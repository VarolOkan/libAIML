
METASOURCES = AUTO

INCLUDES = $(all_includes) -I../std_utils/src

SUBDIRS = aiml
AM_CXXFLAGS = -Wall $(WERROR_CXXFLAG) -ansi -pedantic `xml2-config --cflags`

noinst_PROGRAMS = test_app
test_app_SOURCES = main.cpp

test_app_LDADD = $(top_builddir)/src/libaiml.a $(PCRECPP_LIBS) -L../std_utils/src -lstd_utils
test_app_LDFLAGS = $(XML2_LIBS)

