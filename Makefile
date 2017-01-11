# TODO: Copyright notice etc.

# Settings

ifndef XSD_PATH
XSD_PATH = ../xsd-4.0.0-i686-macosx
endif

NEUROML = NeuroML_v2beta4

XSD = $(XSD_PATH)/bin/xsd

CXXFLAGS = -W -O3 -I$(XSD_PATH)/libxsd -std=c++11 -I/usr/local/include \
  -DSCHEMA_PATH='"$(abspath $(NEUROML).xsd)"'
LDFLAGS = -L/usr/local/lib
LIBS = -lxerces-c
OBJS = $(NEUROML).o NeuroML_custom.o

# Rules

all: test create_net

NeuroML_%.hxx NeuroML_%.cxx: NeuroML_%.xsd Xsd*.txt
	$(XSD) cxx-tree --options-file XsdOptions.txt $<

.SECONDARY: NeuroML_*.hxx NeuroML_*.cxx

%.o: %.cxx $(NEUROML).hxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

test: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

create_net: create_net.o $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
