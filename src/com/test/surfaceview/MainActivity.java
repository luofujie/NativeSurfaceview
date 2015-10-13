package com.test.surfaceview;

import android.app.Activity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.LinearLayout;

public class MainActivity extends Activity{
	TestView view = null;
	int i = 1;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		DisplayMetrics dm = new DisplayMetrics();  
		getWindowManager().getDefaultDisplay().getMetrics(dm);   
		int width=dm.widthPixels;   
		int height=dm.heightPixels;   
		Log.i("JNI_LOG", "screenWidth = "+width+"screenHeight"+height);
		LinearLayout layout = new LinearLayout(this);
		view = new TestView(this);
		view.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				view.drawPicture(i+".bmp");
				i++;
				if(i > 12)
					i=1;
			}
		}); 
		LinearLayout.LayoutParams layoutParam = new LinearLayout.LayoutParams(1080*width/1080,1440*height/1920);
		layout.addView(view,layoutParam);
		setContentView(layout);
	}
}
