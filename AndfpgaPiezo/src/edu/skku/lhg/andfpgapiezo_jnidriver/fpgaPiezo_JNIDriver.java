package edu.skku.lhg.andfpgapiezo_jnidriver;

public class fpgaPiezo_JNIDriver {
	static {
		System.loadLibrary("fpgaPiezo_JNIDriver");
	}
	
	public native void open();
	public native void write(char data);
	public native void close();
}