# makefile for liblas.a
#
#COPTS    = -g -Wall
#COPTS     = -O3 -Wall -Wno-deprecated -DNDEBUG -DUNORDERED
COPTS     = -g -w -DNDEBUG -DUNORDERED ${DEBUG_OPTS}
COMPILER  ?= mpic++
AR  = ar rc
#BITS     = -64

INCLUDE		= -I/usr/include/ -I../../LASzip/src -I../inc -I.

OBJ_LAS		= lasreader.o laswriter.o lasreader_las.o lasreader_bin.o lasreader_qfit.o lasreader_shp.o lasreader_asc.o lasreader_bil.o lasreader_dtm.o lasreader_txt.o lasreadermerged.o lasreaderbuffered.o lasreaderpipeon.o laswriter_las.o laswriter_bin.o laswriter_qfit.o laswriter_wrl.o laswriter_txt.o laswritercompatible.o laswaveform13reader.o laswaveform13writer.o lasutility.o lasfilter.o lastransform.o fopen_compressed.o

OBJ_LAZ		= ../../LASzip/src/laszip.o ../../LASzip/src/lasreadpoint.o ../../LASzip/src/lasreaditemcompressed_v1.o ../../LASzip/src/lasreaditemcompressed_v2.o ../../LASzip/src/laswritepoint.o  ../../LASzip/src/laswriteitemcompressed_v1.o ../../LASzip/src/laswriteitemcompressed_v2.o ../../LASzip/src/integercompressor.o ../../LASzip/src/arithmeticdecoder.o ../../LASzip/src/arithmeticencoder.o ../../LASzip/src/arithmeticmodel.o ../../LASzip/src/lasindex.o ../../LASzip/src/lasquadtree.o ../../LASzip/src/lasinterval.o ../../LASzip/src/lasunzipper.o ../../LASzip/src/laszipper.o 

all: liblas.a

liblas.a: ${OBJ_LAZ} ${OBJ_LAS} 
	$(AR) $@ ${OBJ_LAZ} ${OBJ_LAS}
	cp -p $@ ../lib
	-rm ../../src/*.o

.cpp.o:
	${COMPILER} ${BITS} -c ${COPTS} ${INCLUDE} $< -o $@

.c.o: 
	${COMPILER} ${BITS} -c ${COPTS} ${INCLUDE} $< -o $@

clean:
	rm -rf ${OBJ_LAZ} ${OBJ_LAS} 

clobber:
	rm -rf liblas.a
	rm -rf ${OBJ_LAZ} ${OBJ_LAS}
	rm -rf *~
