.SILENT:

include C:/AndroXStudio/Tools/make_comm

all: $(OBJECTS)
	$(CC) $(CFLAGS) $(EXEC_LDFLAGS) -save-temps -O2 -o lhg_fpga7segment_test_hks_ver $(OBJECTS) \
		$(LLIB)/libgcc.a

	echo 
	echo "**** Install:" /data/local/tmp/lhg_fpga7segment_test_hks_ver "****"
	$(ADB) push lhg_fpga7segment_test_hks_ver /data/local/tmp
	$(ADB) shell chmod 755 /data/local/tmp/lhg_fpga7segment_test_hks_ver
#	echo 
#	echo "**** Run ****"
#	$(ADB) shell /data/local/tmp/lhg_fpga7segment_test_hks_ver

clean:
	rm -f *.o
	rm -f *.i
	rm -f *.s
	rm -f lhg_fpga7segment_test_hks_ver
