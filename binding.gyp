{
  "targets": [
    {
      "target_name": "checkuser",

      "sources": [ "checkuser.cc" ],

      "cflags!": [ "-fno-exceptions" ],

      "cflags_cc!": [ "-fno-exceptions" ],

      "include_dirs": [ "<!(node -p \"require('node-addon-api').include_dirs\")" ],

      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ],
    }
  ]
}