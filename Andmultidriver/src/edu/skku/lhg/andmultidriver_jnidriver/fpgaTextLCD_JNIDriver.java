package edu.skku.lhg.andmultidriver_jnidriver;

public class fpgaTextLCD_JNIDriver {
	static {
		System.loadLibrary("JNIDriver");
	}
	
	public native void on();
	public native void off();
	public native void initialize();
	public native void clear();
	
	public native void print1Line(String str);
	public native void print2Line(String str);
}
