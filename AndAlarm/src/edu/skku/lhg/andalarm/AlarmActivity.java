package edu.skku.lhg.andalarm;

import android.support.v7.app.ActionBarActivity;
import android.app.Dialog;
import android.os.Bundle;
import android.os.Handler;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.text.format.Time;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import edu.skku.lhg.andalarm_jnidriver.fpgaTextLCD_JNIDriver;
import edu.skku.lhg.andalarm_jnidriver.fpgaPiezo_JNIDriver;
import edu.skku.lhg.andalarm_jnidriver.fpga7segment_JNIDriver;

public class AlarmActivity extends ActionBarActivity {
	
	//textlcd
	private fpgaTextLCD_JNIDriver fpgaTextLCD_JNIDriver = new fpgaTextLCD_JNIDriver();
	//piezo
	private fpgaPiezo_JNIDriver fpgaPiezo_JNIDriver = new fpgaPiezo_JNIDriver();
	//segment
	private fpga7segment_JNIDriver fpga7segment_JNIDriver = new fpga7segment_JNIDriver();
	
	BackThread thread = new BackThread();
	AlarmThread runnableObj = new AlarmThread();
	Thread thread2 = new Thread(runnableObj);
	
	protected static final int THREAD_FLAGS_CLOCK = 1; // Clock
	boolean stop = false;
	boolean alarmStop = false;
	String setTime;
	int sound[] = {68, 68, 68, 0};
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_alarm);
		
		// Thread Start
		thread.setDaemon(true);
		thread.start();
		
		thread2.setDaemon(true);
		thread2.start();

        final EditText edit = (EditText)findViewById(R.id.edit);
                
        final Button setButton = (Button)findViewById(R.id.setButton);
        final Button stopButton = (Button)findViewById(R.id.stopButton);
        
        setButton.setOnClickListener(new Button.OnClickListener() {
        	
			@Override
			public void onClick(View arg0) {
				
				setTime = edit.getText().toString();
				final String words = "Alarm rings at";
        		
				fpgaTextLCD_JNIDriver.clear();
        		fpgaTextLCD_JNIDriver.print1Line( words );
        		fpgaTextLCD_JNIDriver.print2Line( setTime );
        		
        		alarmStop = false;
        		
        		Toast.makeText(AlarmActivity.this, "Alarm set successfully", Toast.LENGTH_LONG).show();
			}
        });
        
        stopButton.setOnClickListener(new Button.OnClickListener() {
        	public void onClick(View v) {
        		alarmStop = true;
        		Toast.makeText(AlarmActivity.this, "Alarm Stop", Toast.LENGTH_LONG).show();
        		fpgaPiezo_JNIDriver.write( (char)0 );
        		fpgaTextLCD_JNIDriver.clear();
        	}
        });		
	}
	
	//seg thread
	class BackThread extends Thread {
		@Override
		public void run() {
		while (!stop) {

			fpga7segment_JNIDriver.SegmentIOControl(THREAD_FLAGS_CLOCK);
			int result = 0;

			Time t = new Time();
			t.set(System.currentTimeMillis());
			
			String nowTime = String.valueOf(t.hour) + ":" + String.valueOf(t.minute);

			result = t.hour * 10000 + t.minute * 100 + t.second;
			for (int i = 0; i < 20; i++)
				fpga7segment_JNIDriver.SegmentControl(result);

		} // while
		} // run
	} // BackThread

	//alarm thread
	class AlarmThread implements Runnable {
		@Override
		public void run() {
			while(!stop){
				while(!alarmStop) {
					Time t = new Time();
					t.set(System.currentTimeMillis());

					String nowTime = String.valueOf(t.hour) + ":" + String.valueOf(t.minute);
	
					if (nowTime.equals(setTime)){
						break;
					}
				}
				
				while(!alarmStop){
					for(int i = 0; i < sound.length; ++i){
						fpgaPiezo_JNIDriver.write((char)sound[i]);
						try {
							thread2.sleep(100);
						} catch (InterruptedException e) {
							e.printStackTrace();
						}
						fpgaPiezo_JNIDriver.write( (char)0 );
					}
				}
			}
		}
	}

	//Program exit
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			stop = true;
			thread.interrupt();
			thread2.interrupt();
		}
		return super.onKeyDown(keyCode, event);
	}
	//seg ³¡
	
	@Override
	protected void onResume() {
		fpgaTextLCD_JNIDriver.initialize();
		fpgaPiezo_JNIDriver.open();
		if(fpga7segment_JNIDriver.open("/dev/lhg_fpga7segment") < 0)
			Toast.makeText(AlarmActivity.this, "Driver Open Failed", Toast.LENGTH_SHORT).show();
		
		super.onResume();
	}

	@Override
	protected void onPause() {
		fpgaTextLCD_JNIDriver.clear();
		fpgaTextLCD_JNIDriver.off();
		fpga7segment_JNIDriver.close();
		fpgaPiezo_JNIDriver.close();
		
		super.onPause();
	}

	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.alarm, menu);
		return true;
	}
}