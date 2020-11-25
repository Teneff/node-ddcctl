{
  "targets": [
    {
      "target_name": "nddcctl",
      "sources": [ "src/nddcctl.cc" ],
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
          '-framework Foundation',
          '-framework AppKit'
        ]
      }
    }
  ],
  
}