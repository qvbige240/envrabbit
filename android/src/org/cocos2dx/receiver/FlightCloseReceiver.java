package org.cocos2dx.receiver;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;



public class FlightCloseReceiver extends BroadcastReceiver {
	//hx: for gen4
	private static native void nativeCloseFlight();
    //end
	@Override
	public void onReceive(Context context, Intent intent) {
//    	queueEvent(new Runnable() {
//            @Override
//            public void run() {
                nativeCloseFlight();
//            }
//        });
//		
	}
}
