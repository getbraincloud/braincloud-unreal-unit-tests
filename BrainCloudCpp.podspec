#
#  BrainCloudSDK.podspec
#  BrainCloudSDK C++
#
#  Copyright (c) 2016 BitHeads Inc. All rights reserved.
#

Pod::Spec.new do |s|

  # ―――  Spec Metadata  ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #

  s.name     = "BrainCloudCpp"
  s.version  = "3.5.0"
  s.summary  = "The C++ client library for brainCloud"
  s.homepage = "http://getbraincloud.com/"

  s.ios.deployment_target  = "7.0"
  s.osx.deployment_target  = "10.9"
  s.tvos.deployment_target = "9.0"
  s.watchos.deployment_target = "2.0"

  # ―――  Spec License  ――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #

  s.license                = {:type => "Apache License, Version 2.0", :file => "LICENSE"}

  # ――― Author Metadata  ――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #

  s.authors                = {"Jonathan McCaffrey" => "jonathanm@bitheads.com"}
  s.social_media_url       = "https://twitter.com/braincloudbaas"

  # ――― Source Location ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #

  s.source                 = {:git => "https://github.com/getbraincloud/braincloud-cpp.git", :tag => s.version}

  # ――― Source Code ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #

  s.header_mappings_dir     = "include"
  s.preserve_paths          = "include/*", "include/**/*"
  s.public_header_files     = "include/braincloud/*.h", "include/braincloud/internal/*.h", "include/braincloud/internal/mac/*.h"
  s.source_files            = "src/*.{c,cpp}", "src/mac/*.{c,cpp,mm}", "include/braincloud/*.h", "include/braincloud/internal/*.h", "include/braincloud/internal/mac/*.h"

  # hack for use_frameworks!
  s.xcconfig = {
    'USER_HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/BrainCloudCpp/include"'
  }

  # ――― Project Linking ―――――――――――――――――――――――――――――――――――――――――――――――――――――――――― #

  s.libraries               = 'c++', 'z'
  s.osx.framework           = 'LDAP'
  s.dependency                'SSKeychain'
  s.dependency                'BrainCloudJsonCpp'
end
