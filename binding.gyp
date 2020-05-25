{
  "targets": [
    {
      "target_name": "nddcctl",
      "sources": [ "nddcctl.cc", "functions.cc" ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags": [
        "-kDDCMinReplyDelay=30000000"
      ],
      'xcode_settings': {
        'OTHER_CFLAGS': [
            '-ObjC++'
        ]
      },
      'link_settings': {
        'libraries': [
          '$(SDKROOT)/System/Library/Frameworks/Foundation.framework',
          '$(SDKROOT)/System/Library/Frameworks/AppKit.framework'
        ]
      }
    }
  ],
  
}