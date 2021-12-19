package edu.skku.lhg.andmultidriver_jnidriver;

public class fpga7segment_JNIDriver {
	private boolean mConnectFlag;

	static {
		System.loadLibrary("JNIDriver");
	}

	private native static int openDriver(String path);
	private native static void closeDriver();
	private native static void writeDriver(int value);
	private native static void ioctlDriver(int value);

	public fpga7segment_JNIDriver() {
		mConnectFlag = false;
	}

	public int open(String driver) {
		if(mConnectFlag)
			return -1;
		if (openDriver(driver) > 0){
			mConnectFlag = true;
			return 1;
		}
		else
			return -1;
	}

	public void close() {
	if (!mConnectFlag)
		return;
	mConnectFlag = false;
	closeDriver();
	}

	public void SegmentControl(int value) {
	if (!mConnectFlag)
		return;
	writeDriver(value);
	}

	public void SegmentIOControl(int value) {
	if (!mConnectFlag)
		return;
	ioctlDriver(value);
	}

	protected void finalize() throws Throwable{
	close();
	super.finalize();
	}
}
