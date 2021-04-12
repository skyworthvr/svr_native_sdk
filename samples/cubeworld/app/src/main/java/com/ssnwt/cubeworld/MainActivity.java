package com.ssnwt.cubeworld;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Context;
import android.hardware.display.DisplayManager;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.Display;
import android.view.KeyEvent;

import com.ssnwt.xrapp.XrApp;

import java.lang.reflect.InvocationTargetException;

import static android.hardware.display.DisplayManager.DISPLAY_CATEGORY_PRESENTATION;

public class MainActivity extends NativeActivity {
    static {
        System.loadLibrary( "vrcubeworld" );
    }
    static String TAG = "cubeworld";
    private Thread mThread = null;
    private Activity mActivity;
    private DisplayManager mDisplayManager;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        mActivity = this;
        XrApp.createInstance(mActivity);
        super.onCreate(savedInstanceState);

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        Log.d("test", "key down keycode " + keyCode);
        return super.onKeyDown(keyCode, event);
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        Log.d("test", "key up keycode " + keyCode);
        return super.onKeyUp(keyCode, event);
    }
}
