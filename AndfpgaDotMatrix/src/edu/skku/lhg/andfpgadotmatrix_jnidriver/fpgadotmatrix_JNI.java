package edu.skku.lhg.andfpgadotmatrix_jnidriver;

public class fpgadotmatrix_JNI {
	static {
		System.loadLibrary("fpgadotmatrix_JNI");
	}
	
	public native void DotMatrixControl(String str);
}
