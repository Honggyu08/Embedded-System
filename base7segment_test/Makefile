.SILENT:

include C:/AndroXStudio/Tools/make_comm

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(EXEC_LDFLAGS) -save-temps -O2 -o base7segment_test $(OBJECTS) \
		$(LLIB)/libgcc.a

	echo 
	echo "**** Install:" /data/local/tmp/base7segment_test "****"
	$(ADB) push base7segment_test /data/local/tmp
	$(ADB) shell chmod 755 /data/local/tmp/base7segment_test
	echo 
	echo "**** Run ****"
	$(ADB) shell /data/local/tmp/base7segment_test

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f base7segment_test
