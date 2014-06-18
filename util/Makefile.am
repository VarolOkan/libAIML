
METASOURCES = AUTO

INCLUDES = $(all_includes) -I../std_utils/src

SUBDIRS =
AM_CXXFLAGS = -Wall $(WERROR_CXXFLAG) -ansi -pedantic `xml2-config --cflags`

noinst_PROGRAMS = aiml_util
aiml_util_SOURCES = parser.cpp main.cpp
noinst_HEADERS = parser.h

aiml_util_LDADD   = $(top_builddir)/src/libaiml.a $(PCRECPP_LIBS) $(V8_LIBS) -L../std_utils/src -lstd_utils
aiml_util_LDFLAGS = $(XML2_LIBS)

