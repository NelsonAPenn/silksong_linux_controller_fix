# Known configs

If you have a controller in this list, a config is provided that you should be
able to use. This is by no means a complete list; rather, it is provided to save
people the time of compiling and the program in this repository (and SDL3 if not
packaged by their distro).

If you have a controller in this list but the config provided still does not
work, please run the program described in the README and try the config it
provides before filing an issue. There can be minor differences in the VID / PID
for the controller.

## 8BitDo Ultimate 2 Wireless Controller

Steam launch options:

```sh
SDL_GAMECONTROLLERCONFIG='03000000c82d00000b31000014010000,8BitDo Ultimate 2 Wireless Controller,a:b0,b:b1,x:b2,y:b3,back:b6,guide:b8,start:b7,leftstick:b9,rightstick:b10,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a3,righty:a4,lefttrigger:a2,righttrigger:a5,platform:Linux,' %command%
```

Just the environment variable:

```sh
SDL_GAMECONTROLLERCONFIG='03000000c82d00000b31000014010000,8BitDo Ultimate 2 Wireless Controller,a:b0,b:b1,x:b2,y:b3,back:b6,guide:b8,start:b7,leftstick:b9,rightstick:b10,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a3,righty:a4,lefttrigger:a2,righttrigger:a5,platform:Linux,'
```

## 8BitDo Ultimate 2C Wireless Controller

Steam launch options:

```sh
SDL_GAMECONTROLLERCONFIG='03000000c82d00000a31000014010000,8BitDo Ultimate 2C Wireless Controller,a:b0,b:b1,x:b2,y:b3,back:b6,guide:b8,start:b7,leftstick:b9,rightstick:b10,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a3,righty:a4,lefttrigger:a2,righttrigger:a5,platform:Linux,' %command%
```

Just the environment variable:

```sh
SDL_GAMECONTROLLERCONFIG='03000000c82d00000a31000014010000,8BitDo Ultimate 2C Wireless Controller,a:b0,b:b1,x:b2,y:b3,back:b6,guide:b8,start:b7,leftstick:b9,rightstick:b10,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a3,righty:a4,lefttrigger:a2,righttrigger:a5,platform:Linux,'
```

## 8BitDo Ultimate 2C Wired Controller

Steam launch options:

```sh
SDL_GAMECONTROLLERCONFIG='03000000c82d00001d30000011010000,8BitDo Ultimate 2C Wired Controller,a:b0,b:b1,x:b3,y:b4,back:b10,guide:b12,start:b11,leftstick:b13,rightstick:b14,leftshoulder:b6,rightshoulder:b7,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a2,righty:a3,lefttrigger:a5,righttrigger:a4,platform:Linux,' %command%
```

Just the environment variable:

```sh
SDL_GAMECONTROLLERCONFIG='03000000c82d00001d30000011010000,8BitDo Ultimate 2C Wired Controller,a:b0,b:b1,x:b3,y:b4,back:b10,guide:b12,start:b11,leftstick:b13,rightstick:b14,leftshoulder:b6,rightshoulder:b7,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,leftx:a0,lefty:a1,rightx:a2,righty:a3,lefttrigger:a5,righttrigger:a4,platform:Linux,'
```

## Xbox Series X Controller

Steam launch options:

```sh
SDL_GAMECONTROLLERCONFIG='030000005e040000120b000005050000,Xbox Series X Controller,a:b0,b:b1,x:b2,y:b3,back:b6,guide:b8,start:b7,leftstick:b9,rightstick:b10,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,misc1:b11,leftx:a0,lefty:a1,rightx:a3,righty:a4,lefttrigger:a2,righttrigger:a5,platform:Linux,' %command%
```

Just the environment variable:

```sh
SDL_GAMECONTROLLERCONFIG='030000005e040000120b000005050000,Xbox Series X Controller,a:b0,b:b1,x:b2,y:b3,back:b6,guide:b8,start:b7,leftstick:b9,rightstick:b10,leftshoulder:b4,rightshoulder:b5,dpup:h0.1,dpdown:h0.4,dpleft:h0.8,dpright:h0.2,misc1:b11,leftx:a0,lefty:a1,rightx:a3,righty:a4,lefttrigger:a2,righttrigger:a5,platform:Linux,'
```
