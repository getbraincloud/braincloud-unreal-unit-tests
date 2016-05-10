package com.bitheads.braincloud;

import java.util.Date;
import java.util.Locale;
import java.util.TimeZone;

public class AndroidBridge {

	public native static void setCountryCode(String countryCode);
	public native static void setLanguageCode(String languageCode);
	public native static void setTimezoneOffset(float timezoneOffset);
	
	public static void initializeLocale()
	{
		Locale locale = Locale.getDefault();
		String countryCode = locale.getCountry();
		String languageCode = locale.getLanguage();
		
		TimeZone tz = TimeZone.getDefault();
		Date d = new Date();
		float timezoneOffset = tz.getOffset(d.getTime()) / (float) (60 * 60 * 1000);
		
		AndroidBridge.setCountryCode(countryCode);
		AndroidBridge.setLanguageCode(languageCode);
		AndroidBridge.setTimezoneOffset(timezoneOffset);
	}
}
