package com.test.surfaceview;

import android.content.Context;
import android.media.MediaPlayer;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class TestView extends SurfaceView implements SurfaceHolder.Callback{

	public static String TAG = "TestView"; 
	public TestNative mNative = new TestNative();
	private SurfaceHolder holder;
	Context mContext;
	public TestView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		holder = getHolder();
		holder.addCallback(this);
		mContext = context;
	}
	public void drawPicture(String path)
	{
		mNative.Draw(path);
		mNative.TestFFMPEG();
		//mNative.ShowYuv();
	}
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		Log.i(TAG, "surfaceCreated");
	}
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
		Log.i(TAG, "surfaceChanged");
		mNative.Init(holder.getSurface(),mContext.getAssets());
	}
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		Log.i(TAG, "surfaceDestroyed");
		mNative.Destroye();
	}
	
}
