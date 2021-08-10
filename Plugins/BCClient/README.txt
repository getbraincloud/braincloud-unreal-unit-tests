// BrainCloud Unreal Plugin
// Copyright 2021 bitHeads, Inc. All Rights Reserved.


/* INSTALLATION */

1.  Open your Unreal Project's root folder (where the *.uproject file is)
2.  Open the Plugins folder, or create it if it does not exist
3.  Copy the BCClient folder into the Plugins folder
4.  If your project is NOT Blueprint only, be sure to regenerate your code project files
5.  Installation complete!

/* Documentation and Tutorials */

Visit our API Docs site here:  http://apidocs.braincloudservers.com/


/* NOTES */

To manipulate JSON in Blueprint another plugin is required.
We recommend VaRest, which you can find here: https://github.com/ufna/VaRest


/* BREAKING CHANGES */

When methods are deprecated and removed Unreal will throw exceptions when opening 
Blueprints that contain these functions.

Ensure you have removed these functions from your blueprints before updating to the new
version of the plugin.  If you experience issues, roll back to to the previous version and
ensure you have not missed removal of these deprecated calls.