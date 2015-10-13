package com.test.surfaceview;

import android.content.res.AssetManager;
import android.view.Surface;

public class TestNative {
	static{
		System.loadLibrary("TestSufaceView");
	}
	native void Init(Surface surface,AssetManager assetManager);
	native void Draw(String path);
	native void ShowYuv();
	native void Destroye();
	native void TestFFMPEG();
}
