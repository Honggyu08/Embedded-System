package edu.skku.sm5baseled;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.Toast;
import edu.skku.sm5baseled_jnidriver.BaseLed_JNIDriver;

public class MainActivity extends Activity {

BaseLed_JNIDriver mDriver = new BaseLed_JNIDriver();
//int LedData;
byte[] iLedData = {0,0,0,0,0,0,0,0};
CheckBox Led1, Led2, Led3, Led4, Led5, Led6, Led7, Led8;
@Override
protected void onCreate(Bundle savedInstanceState) {
	super.onCreate(savedInstanceState);
	setContentView(R.layout.activity_main);

	Led1 = (CheckBox) findViewById(R.id.checkBox1);
	Led2 = (CheckBox) findViewById(R.id.checkBox2);
	Led3 = (CheckBox) findViewById(R.id.checkBox3);
	Led4 = (CheckBox) findViewById(R.id.checkBox4);
	Led5 = (CheckBox) findViewById(R.id.checkBox5);
	Led6 = (CheckBox) findViewById(R.id.checkBox6);
	Led7 = (CheckBox) findViewById(R.id.checkBox7);
	Led8 = (CheckBox) findViewById(R.id.checkBox8);
	
	Led1.setChecked(false);
	Led1.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
	if(Led1.isChecked())
	iLedData[0] = 1;
	else
	iLedData[0] = 0;

		mDriver.write(iLedData);
	}
	});
	
	Led2.setChecked(false);
	Led2.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
	if(Led2.isChecked())
	iLedData[1] = 1;
	else
	iLedData[1] = 0;

		mDriver.write(iLedData);
	}
	});
	
	Led3.setChecked(false);
	Led3.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
	if(Led3.isChecked())
	iLedData[2] = 1;
	else
	iLedData[2] = 0;

		mDriver.write(iLedData);
	}
	});
	
	Led4.setChecked(false);
	Led4.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
	if(Led4.isChecked())
	iLedData[3] = 1;
	else
	iLedData[3] = 0;

		mDriver.write(iLedData);
	}
	});
	
	Led5.setChecked(false);
	Led5.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
	if(Led5.isChecked())
	iLedData[4] = 1;
	else
	iLedData[4] = 0;

		mDriver.write(iLedData);
	}
	});
	
	Led6.setChecked(false);
	Led6.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
	if(Led6.isChecked())
	iLedData[5] = 1;
	else
	iLedData[5] = 0;

		mDriver.write(iLedData);
	}
	});
	
	Led7.setChecked(false);
	Led7.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
	if(Led7.isChecked())
	iLedData[6] = 1;
	else
	iLedData[6] = 0;

		mDriver.write(iLedData);
	}
	});
	
	Led8.setChecked(false);
	Led8.setOnClickListener(new CheckBox.OnClickListener() {
	public void onClick(View v) {
		if(Led8.isChecked())
	      iLedData[7] = 1;
		else
	      iLedData[7] = 0;

	        mDriver.write(iLedData);
	}
	});
	}
	
	@Override
	protected void onPause() {
	mDriver.close();
	super.onPause();
	}

	@Override
	protected void onResume() {
	if(mDriver.open("/dev/hks_fpgaled") < 0)  //¿ø·¡ baseled 
	Toast.makeText(getApplicationContext(), "Driver Open failed", Toast.LENGTH_LONG).show();
	super.onResume();
	}
	}