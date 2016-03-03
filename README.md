# brainCloud C++ Client Library

Thanks for downloading the brainCloud C++ client library! Here are a few notes to get you started. Further information about the brainCloud API, including example Tutorials can be found here:

http://getbraincloud.com/apidocs/

If you haven't signed up or you want to log into the brainCloud portal, you can do that here:

https://portal.braincloudservers.com/

## Installation

The library is distributed through `CocoaPods`. In order to install the library, simply add the following to your `Podfile`.

```ruby
pod 'BrainCloudCpp'
```

If you're a newcomer to the `CocoaPods` world, you can find documentation on how to set up your Xcode project:

https://guides.cocoapods.org/

## Troubleshooting

Here are a few common errors that you may see on your first attempt to connect to brainCloud.

- **Game id not set**: Verify you've set up the game id and game secret correctly in the `initialize()` method.
- **Platform not enabled**: Verify you've enabled your platform on the portal.

If you're still having issues, log into the portal and give us a shout through the help system (bottom right icon with the question mark and chat bubble).

