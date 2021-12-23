package edu.skku.lhg.andalarm_jnidriver;

public class fpgaPiezo_JNIDriver {
	static {
		System.loadLibrary("JNIDriver");
	}
	
	public native void open();
	public native void write(char data);
	public native void close();
}
