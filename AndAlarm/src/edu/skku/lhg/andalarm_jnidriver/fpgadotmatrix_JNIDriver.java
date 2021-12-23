package edu.skku.lhg.andalarm_jnidriver;

public class fpgadotmatrix_JNIDriver {
	static {
		System.loadLibrary("JNIDriver");
	}
	
	public native void DotMatrixControl(String str);
}
