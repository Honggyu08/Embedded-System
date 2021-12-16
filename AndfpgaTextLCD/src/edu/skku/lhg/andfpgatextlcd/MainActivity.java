package edu.skku.lhg.andfpgatextlcd;

import edu.skku.lhg.andfpgatextlcd_jnidriver.fpgaTextLCD_JNIDriver;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity {

	private fpgaTextLCD_JNIDriver fpgaTextLCD_JNIDriver = new fpgaTextLCD_JNIDriver();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
        final EditText edit1 = (EditText)findViewById(R.id.edit1);
        final EditText edit2 = (EditText)findViewById(R.id.edit2);
                
        final Button writeButton = (Button)findViewById(R.id.writeButton);
        final Button clearButton = (Button)findViewById(R.id.clearButton);
        
        writeButton.setOnClickListener(new Button.OnClickListener() {
        	
			@Override
			public void onClick(View arg0) {
				final String str1 = edit1.getText().toString();
				Toast.makeText(MainActivity.this, str1, Toast.LENGTH_SHORT).show();
        		final String str2 = edit2.getText().toString();
        		fpgaTextLCD_JNIDriver.clear();
        		fpgaTextLCD_JNIDriver.print1Line(str1);
        		fpgaTextLCD_JNIDriver.print2Line(str2);
			}
        });
        
        clearButton.setOnClickListener(new Button.OnClickListener() {
        	public void onClick(View v) {
        		fpgaTextLCD_JNIDriver.clear();
        	}
        });		
	}
	
	@Override
	protected void onResume() {
		fpgaTextLCD_JNIDriver.initialize();
		super.onResume();
	}

	@Override
	protected void onPause() {
		fpgaTextLCD_JNIDriver.off();
		super.onPause();
	}

	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
