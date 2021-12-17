.SILENT:

include C:/AndroXStudio/Tools/make_comm

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(EXEC_LDFLAGS) -save-temps -O2 -o baseled_test $(OBJECTS) \
		$(LLIB)/libgcc.a

	echo 
	echo "**** Install:" /data/local/tmp/baseled_test "****"
	$(ADB) push baseled_test /data/local/tmp
	$(ADB) shell chmod 755 /data/local/tmp/baseled_test
	echo 
	echo "**** Run ****"
	$(ADB) shell /data/local/tmp/baseled_test

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f baseled_test
