package edu.skku.andbase7segment;

import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import edu.skku.andbase7segment_jnidriver.Base7SegmentJNIDriver;


public class MainActivity extends ActionBarActivity {

	Base7SegmentJNIDriver mDriver = new Base7SegmentJNIDriver();
	EditText input;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	
		input = (EditText) findViewById(R.id.editText1);
	}

	public void onButton1Clicked(View v) {
		int value = Integer.parseInt(input.getText().toString());
		if (value >255) {
			Toast.makeText(getApplicationContext(), "Input range : 0~255", Toast.LENGTH_LONG).show();
			return;
		}
			
		// set 7Segment
		mDriver.Set_7Segment(value);
	}

	@Override
	protected void onPause() {
		mDriver.close();
		super.onPause();
	}
	@Override
	protected void onResume() {
		if(mDriver.open("/dev/base7segment") < 0)
			Toast.makeText(MainActivity.this, "Driver Open Failed", Toast.LENGTH_SHORT).show();
		
		super.onResume();
	}
}
