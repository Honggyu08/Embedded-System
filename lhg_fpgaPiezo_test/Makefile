.SILENT:

include C:/AndroXStudio/Tools/make_comm

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(EXEC_LDFLAGS) -save-temps -O2 -o lhg_fpgaPiezo_test $(OBJECTS) \
		$(LLIB)/libgcc.a

	echo 
	echo "**** Install:" /data/local/tmp/lhg_fpgaPiezo_test "****"
	$(ADB) push lhg_fpgaPiezo_test /data/local/tmp
	$(ADB) shell chmod 755 /data/local/tmp/lhg_fpgaPiezo_test
	echo 
	echo "**** Run ****"
	$(ADB) shell /data/local/tmp/lhg_fpgaPiezo_test

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f lhg_fpgaPiezo_test
