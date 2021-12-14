package edu.skku.andbase7segment_jnidriver;

public class Base7SegmentJNIDriver {
	private boolean mConnectFlag;
	
	static {
		System.loadLibrary("Base7SegmentJNIDriver");
	}
	
	private native static int openDriver(String path);
	private native static void closeDriver();
	private native static void writeDriver(int data);
	
	public Base7SegmentJNIDriver() {
		mConnectFlag = false;
	}
	
	public int open(String driver) {
		if (mConnectFlag)
			return -1;
		
		if(openDriver(driver) > 0) {
			mConnectFlag = true;
			return 1;
		}
		else 
			return -2;
	}
	
	public void close() {
		if (!mConnectFlag)
			return;
		mConnectFlag = false;
		closeDriver();
	}

	protected void finalize() throws Throwable {
		close();
		super.finalize();
	}
	
	public void Set_7Segment(int data) {
		if (!mConnectFlag)
			return;
		writeDriver(data);
	}
		
}
