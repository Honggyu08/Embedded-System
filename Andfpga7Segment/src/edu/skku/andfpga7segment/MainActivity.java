package edu.skku.andfpga7segment;

import android.app.Dialog;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.text.format.Time;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import edu.skku.andfpga7segment_jnidriver.fpga7segment_JNIDriver;

public class MainActivity extends ActionBarActivity {
fpga7segment_JNIDriver mDriver = new fpga7segment_JNIDriver();
BackThread thread = new BackThread(); 
protected static final int THREAD_FLAGS_PRINT = 0; // Countdown
protected static final int THREAD_FLAGS_CLOCK = 1; // Clock
protected static final int DIALOG_SIMPLE_MESSAGE = 1;
int flag = -1; 
boolean stop = false;
int count = 0; 

@Override
public void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	setContentView(R.layout.activity_main);

	// Thread Start
	thread.setDaemon(true);
	thread.start();

	final EditText digit = (EditText) findViewById(R.id.editText1);
	final Button Input = (Button) findViewById(R.id.button1);
	final Button clock = (Button) findViewById(R.id.button2);
	final Button segOff = (Button) findViewById(R.id.button3);

	Input.setOnClickListener(new Button.OnClickListener() {
	public void onClick(View v) {
		if ((Integer.parseInt(digit.getText().toString()) > 1000000) 
			|| (Integer.parseInt(digit.getText().toString()) < 1)){
			showDialog(DIALOG_SIMPLE_MESSAGE);
			return;
		}
		count = Integer.parseInt(digit.getText().toString());
		flag = THREAD_FLAGS_PRINT;
	}
	});

	clock.setOnClickListener(new Button.OnClickListener() {
	public void onClick(View v) {
		flag = THREAD_FLAGS_CLOCK;
	}
	});

	segOff.setOnClickListener(new Button.OnClickListener() {
	public void onClick(View v) {
		flag = -1;
	}
	});
}

class BackThread extends Thread {
public void run() {
while (!stop) {
	switch (flag) {
	default:
	// do nothing
	break;
	case THREAD_FLAGS_PRINT:
 	// Countdown
	mDriver.SegmentIOControl(THREAD_FLAGS_PRINT);
	while (count > 0 && flag == THREAD_FLAGS_PRINT) {
		for (int i = 0; i < 140 && flag == THREAD_FLAGS_PRINT; i++) {
			mDriver.SegmentControl(count);
		}
		count--;
	}
	if (count <= 0)
		flag = -1;
	break;

	case THREAD_FLAGS_CLOCK:
	// Clock
	mDriver.SegmentIOControl(THREAD_FLAGS_CLOCK);
	int result = 0;

	Time t = new Time();
	t.set(System.currentTimeMillis());
	result = t.hour * 10000 + t.minute * 100 + t.second;
	
	for (int i = 0; i < 20; i++)
		mDriver.SegmentControl(result);
	break;
	}
} // while
} // run
} // BackThread

//Program exit
@Override
public boolean onKeyDown(int keyCode, KeyEvent event) {
	if (keyCode == KeyEvent.KEYCODE_BACK) {
		flag = -1;
		stop = true;
		thread.interrupt();
	}
	return super.onKeyDown(keyCode, event);
}

//Exception processing for input countdown value
@Override
protected Dialog onCreateDialog(int id) {
	// TODO Auto-generated method stub
	Dialog d = new Dialog(MainActivity.this);
	Window window = d.getWindow();
	window.setFlags(WindowManager.LayoutParams.FIRST_APPLICATION_WINDOW,
	WindowManager.LayoutParams.FIRST_APPLICATION_WINDOW);

	switch (id) {
	case DIALOG_SIMPLE_MESSAGE:
		d.setTitle("input digit: 1 to 999999");
		d.show();
		return d;
	}
	return super.onCreateDialog(id);
}

@Override
protected void onResume() {
	if(mDriver.open("/dev/lhg_fpga7segment") < 0)
		Toast.makeText(getApplicationContext(), "Driver Open failed", 			Toast.LENGTH_LONG).show();
	super.onResume();
}

@Override
protected void onPause() {
	mDriver.close();
	super.onPause();
}
}