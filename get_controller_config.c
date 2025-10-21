/*
 * Get SDL2 Controller config for controller with only SDL3 support.
 *
 * This program is part of a fix for controller issues with 8BitDo controllers
 * on Silksong on Linux, although it should work for other newly supported
 * controllers. 
 *
 * Steps for fix created by kakonema. Code written by Nelson Penn, provided via
 * the Unlicense.
 */
#include <SDL3/SDL_guid.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_joystick.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  if (!SDL_Init(SDL_INIT_JOYSTICK))
  {
    fprintf(stderr, "SDL failed to init\n");
    exit(1);
  }
  int exit_code, num_joysticks = 0;
  SDL_JoystickID* joysticks = SDL_GetJoysticks(&num_joysticks);
  for (size_t i = 0; i < num_joysticks; i++)
  {
    struct SDL_Joystick* joystick = SDL_OpenJoystick(joysticks[i]);
    if (joystick == NULL)
    {
      fprintf(stderr, "Failed to open joystick\n");
      exit_code = 1;
      goto free_joysticks;
    }
    const char* name = SDL_GetJoystickName(joystick);
    struct SDL_GUID guid = SDL_GetJoystickGUID(joystick);
    char buf[33];
    SDL_GUIDToString(guid, buf, 33);
    
    /*
    * For SDL2 compatibility, CRC bytes must be zeroed out.
    */
    char* mapping = SDL_GetGamepadMappingForGUID(guid);
    if (!mapping) 
    {
      printf("Joystick %zu (%s) could not be mapped: %s. Continuing", i, name, SDL_GetError());
      continue; // Not a gamepad
    }
    
    printf("\033[34mJoystick %zu: %s\033[0m\n", i, name);
    for (size_t guid_byte = 2; guid_byte < 4; guid_byte++)
    {
      mapping[guid_byte * 2] = '0';
      mapping[guid_byte * 2 + 1] = '0';
    }
    printf("\tTo use this controller in Silksong, set the following environment variable when running the game:\n\n");
    printf("\tSDL_GAMECONTROLLERCONFIG='%s'\n\n", mapping);
    printf("\tFor example, Steam launch options would be:\n\n");
    printf("\tSDL_GAMECONTROLLERCONFIG='%s' %%command%%\n\n", mapping);

    SDL_CloseJoystick(joystick);
    SDL_free(mapping);
  }

  free_joysticks:
    SDL_free(joysticks);
  return exit_code;
}
