.SILENT:

include C:/AndroXStudio/Tools/make_comm

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(EXEC_LDFLAGS) -save-temps -O2 -o lhg_fpgaDotMatrix_test $(OBJECTS) \
		$(LLIB)/libgcc.a

	echo 
	echo "**** Install:" /data/local/tmp/lhg_fpgaDotMatrix_test "****"
	$(ADB) push lhg_fpgaDotMatrix_test /data/local/tmp
	$(ADB) shell chmod 755 /data/local/tmp/lhg_fpgaDotMatrix_test
	echo 
	echo "**** Run ****"
	#$(ADB) shell /data/local/tmp/lhg_fpgaDotMatrix_test

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f lhg_fpgaDotMatrix_test
