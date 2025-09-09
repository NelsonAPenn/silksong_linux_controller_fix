## Silksong on Linux controller fix

The methods in this repository do not yet fix the issue. Currently it is a
collection of information and fixes that have been attempted. If you are
knowlegeable about SDL and/or Unity and this gives you any ideas, you are
encouraged to contribute.

## Background

On the native Linux version of Silksong, the game acts very strangely once you
get abilities using the right or left triggers. This includes, but is not
limited to, the 8BitDo Ultimate 2C Wireless controller.

The game is normal on startup before right trigger has ever been pressed. Once
it has been pressed, it seems to activate on a soft pull and not deactivate, or
briefly deactivate then reactivate unpredictably. When Hornet climbs up a ledge,
Swift Steps will be reactivated even if it is off and the button is not pressed
in.

The same issue affected Hollow Knight, with the Crystal Dash ability. However,
this could be worked around by setting the SDL_DYNAMIC_API environment variable
in the launch options in Steam. For example:

```
SDL_DYNAMIC_API=/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0 %command%
```

The same does not work in Silksong, however. Occurrences of `SDL_DYNAMIC_API`
are present in UnityPlayer.so in Hollow Knight, but not in Silksong. Running
Hollow Knight with LD_DEBUG on with no launch options results in no mention of
SDL, indicating a statically linked version was used. With the launch option, it
shows that the library provided is loaded. For Silksong, no system SDL is
loaded, whether or not an SDL_DYNAMIC_API or SDL3_DYNAMIC_API environment
variable is set.

That being said, the only exported symbol from UnityPlayer.so is
`PlayerMain(int, char**)`, so the SDL-related text in this binary may not be the
place or the only place SDL is statically linked.

## Potentially relevant Unity info

- [description of files in packaged game on Linux](https://docs.unity3d.com/6000.2/Documentation/Manual/build-for-linux.html)
- [legacy InputManager API](https://docs.unity3d.com/2022.3/Documentation/Manual/class-InputManager.html)

## `sdl2-jstest` results

`sdl2-jstest` was used to test the trigger inputs of the controller. The trigger
inputs were axes whose value range from i16::MIN to i16::MAX.

## Hypotheses about why the trigger acts the way it does

One possible explanation of the behavior is that the trigger value is treated
like a button instead of an axis. It's hypothetically initialized to 0, which
explains the normal behavior before it has ever been pressed. After the first
time the trigger is pulled, the axis value is nonzero in every case except for a
pull that is exactly halfway. So, it is as if the button is being held in most
cases, except for brief lapses of being off when the halfway point is hit.

Another possible explanation of the behavior is that the controller
configuration is not present in the statically linked version of SDL that is
used. More on this below.

Lastly, taking a wild guess: Hollow Knight and Silksong use the legacy
InputManager API, specifically Input.GetButtonDown for the trigger axis. And
going out on a limb, that doesn't work with with the trigger buttons of many
8BitDo controllers.

## Possible solutions

### Creating a virtual joystick device

If the first hypothesis is correct, the problem could be solved that translates
the trigger axis to be a button instead. So if the key report is i16::MIN, the
virtual button value is 0, otherwise it is 1. What would need to be figured out
is how to create this virtual device and make sure the game ignores inputs from
the original.

### Adding the controller configuration into the static copy of SDL

If the second hypothesis is correct, the problem could be solved by injecting
the correct controller configuration into the binary. This was attempted: this
repository contains a `controller_injector.c` program that goes through the SDL
joystick database in the UnityPlayer.so binary and replaces configurations with
a matching length with the desired controller configuration. Several
configurations were tested, including the verbatim config resulting from
`sdl2-jstest`. The game did not crash, but the same wacky behavior was exhibited
in all tests. It could be that the correct controller configuration is still not
being used after patching the binary, but it is also likely that this isn't the
root cause of the issue given the results of testing.
